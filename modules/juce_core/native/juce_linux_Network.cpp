/*
  ==============================================================================

   This file is part of the JUCE library.
   Copyright (c) 2016 - ROLI Ltd.

   Permission is granted to use this software under the terms of the ISC license
   http://www.isc.org/downloads/software-support-policy/isc-license/

   Permission to use, copy, modify, and/or distribute this software for any
   purpose with or without fee is hereby granted, provided that the above
   copyright notice and this permission notice appear in all copies.

   THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH REGARD
   TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
   FITNESS. IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT,
   OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
   USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
   TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
   OF THIS SOFTWARE.

   -----------------------------------------------------------------------------

   To release a closed-source product which uses other parts of JUCE not
   licensed under the ISC terms, commercial licenses are available: visit
   www.juce.com for more information.

  ==============================================================================
*/

void MACAddress::findAllAddresses (Array<MACAddress>& result)
{
    const int s = socket (AF_INET, SOCK_DGRAM, 0);
    if (s != -1)
    {
        struct ifaddrs* addrs = nullptr;

        if (getifaddrs (&addrs) != -1)
        {
            for (struct ifaddrs* i = addrs; i != nullptr; i = i->ifa_next)
            {
                struct ifreq ifr;
                strcpy (ifr.ifr_name, i->ifa_name);
                ifr.ifr_addr.sa_family = AF_INET;

                if (ioctl (s, SIOCGIFHWADDR, &ifr) == 0)
                {
                    MACAddress ma ((const uint8*) ifr.ifr_hwaddr.sa_data);

                    if (! ma.isNull())
                        result.addIfNotAlreadyThere (ma);
                }
            }

            freeifaddrs (addrs);
        }

        close (s);
    }
}


bool JUCE_CALLTYPE Process::openEmailWithAttachments (const String& /* targetEmailAddress */,
                                                      const String& /* emailSubject */,
                                                      const String& /* bodyText */,
                                                      const StringArray& /* filesToAttach */)
{
    jassertfalse;    // xxx todo
    return false;
}

//==============================================================================
#if ! JUCE_USE_CURL
class WebInputStream::Pimpl
{
public:
    /*    WebInputStream (const String& address_, bool isPost_, const MemoryBlock& postData_,
                    URL::OpenStreamProgressCallback* progressCallback, void* progressCallbackContext,
                    const String& headers_, int timeOutMs_, StringPairArray* responseHeaders,
                    const int maxRedirects, const String& httpRequestCmd_)
      : statusCode (0), socketHandle (-1), levelsOfRedirection (0),
        address (address_), headers (headers_), postData (postData_), contentLength (-1), position (0),
        finished (false), isPost (isPost_), timeOutMs (timeOutMs_), numRedirectsToFollow (maxRedirects),
        httpRequestCmd (httpRequestCmd_), chunkEnd (0), isChunked (false), readingChunk (false)*/
    Pimpl (WebInputStream& pimplOwner, const URL& urlToCopy, const bool shouldUsePost)
        : statusCode (0), owner (pimplOwner), url (urlToCopy), socketHandle (-1), levelsOfRedirection (0),
          contentLength (-1), position (0), finished  (false), isPost (shouldUsePost), timeOutMs (0),
          numRedirectsToFollow (5), httpRequestCmd (shouldUsePost ? "POST" : "GET"), chunkEnd (0),
          isChunked (false), readingChunk (false)
    {}

    ~Pimpl()
    {
        closeSocket();
    }

    //==============================================================================
    // WebInputStream methods
    void withExtraHeaders (const String& extraHeaders)
    {
        if (! headers.endsWithChar ('\n') && headers.isNotEmpty())
            headers << "\r\n";

        headers << extraHeaders;

        if (! headers.endsWithChar ('\n') && headers.isNotEmpty())
            headers << "\r\n";
    }

    void withCustomRequestCommand (const String& customRequestCommand)    { httpRequestCmd = customRequestCommand; }
    void withConnectionTimeout (int timeoutInMs)                          { timeOutMs = timeoutInMs; }
    void withNumRedirectsToFollow (int maxRedirectsToFollow)              { numRedirectsToFollow = maxRedirectsToFollow; }
    StringPairArray getRequestHeaders() const                             { return WebInputStream::parseHttpHeaders (headers); }

    StringPairArray getResponseHeaders() const
    {
        StringPairArray responseHeaders;
        if (! isError())
        {
            for (int i = 0; i < headerLines.size(); ++i)
            {
                const String& headersEntry = headerLines[i];
                const String key (headersEntry.upToFirstOccurrenceOf (": ", false, false));
                const String value (headersEntry.fromFirstOccurrenceOf (": ", false, false));
                const String previousValue (responseHeaders [key]);
                responseHeaders.set (key, previousValue.isEmpty() ? value : (previousValue + "," + value));
            }
        }

        return responseHeaders;
    }

    int getStatusCode() const                                             { return statusCode; }

    bool connect (WebInputStream::Listener* listener)
    {
        address = url.toString (! isPost);
        statusCode = createConnection (listener, numRedirectsToFollow);

        return (statusCode != 0);
    }

    void cancel()
    {
        statusCode = -1;
        finished = true;

        closeSocket();
    }

    //==============================================================================w
    bool isError() const                 { return socketHandle < 0; }
    bool isExhausted()                   { return finished; }
    int64 getPosition()                  { return position; }
    int64 getTotalLength()               { return contentLength; }

    int read (void* buffer, int bytesToRead)
    {
        if (finished || isError())
            return 0;

        if (isChunked && ! readingChunk)
        {
            if (position >= chunkEnd)
            {
                const ScopedValueSetter<bool> setter (readingChunk, true, false);
                MemoryOutputStream chunkLengthBuffer;
                char c = 0;

                if (chunkEnd > 0)
                {
                    if (read (&c, 1) != 1 || c != '\r'
                         || read (&c, 1) != 1 || c != '\n')
                    {
                        finished = true;
                        return 0;
                    }
                }

                while (chunkLengthBuffer.getDataSize() < 512 && ! (finished || isError()))
                {
                    if (read (&c, 1) != 1)
                    {
                        finished = true;
                        return 0;
                    }

                    if (c == '\r')
                        continue;

                    if (c == '\n')
                        break;

                    chunkLengthBuffer.writeByte (c);
                }

                const int64 chunkSize = chunkLengthBuffer.toString().trimStart().getHexValue64();

                if (chunkSize == 0)
                {
                    finished = true;
                    return 0;
                }

                chunkEnd += chunkSize;
            }

            if (bytesToRead > chunkEnd - position)
                bytesToRead = static_cast<int> (chunkEnd - position);
        }

        fd_set readbits;
        FD_ZERO (&readbits);
        FD_SET (socketHandle, &readbits);

        struct timeval tv;
        tv.tv_sec = jmax (1, timeOutMs / 1000);
        tv.tv_usec = 0;

        if (select (socketHandle + 1, &readbits, 0, 0, &tv) <= 0)
            return 0;   // (timeout)

        const int bytesRead = jmax (0, (int) recv (socketHandle, buffer, (size_t) bytesToRead, MSG_WAITALL));
        if (bytesRead == 0)
            finished = true;

        if (! readingChunk)
            position += bytesRead;

        return bytesRead;
    }

    bool setPosition (int64 wantedPos)
    {
        if (isError())
            return false;

        if (wantedPos != position)
        {
            finished = false;

            if (wantedPos < position)
                return false;

            int64 numBytesToSkip = wantedPos - position;
            const int skipBufferSize = (int) jmin (numBytesToSkip, (int64) 16384);
            HeapBlock<char> temp ((size_t) skipBufferSize);

            while (numBytesToSkip > 0 && ! isExhausted())
                numBytesToSkip -= read (temp, (int) jmin (numBytesToSkip, (int64) skipBufferSize));
        }

        return true;
    }

    //==============================================================================
    int statusCode;

private:
    WebInputStream& owner;
    URL url;
    int socketHandle, levelsOfRedirection;
    StringArray headerLines;
    String address, headers;
    MemoryBlock postData;
    int64 contentLength, position;
    bool finished;
    const bool isPost;
    int timeOutMs;
    int numRedirectsToFollow;
    String httpRequestCmd;
    int64 chunkEnd;
    bool isChunked, readingChunk;

    void closeSocket (bool resetLevelsOfRedirection = true)
    {
        if (socketHandle >= 0)
            close (socketHandle);

        socketHandle = -1;
        if (resetLevelsOfRedirection)
            levelsOfRedirection = 0;
    }

    int createConnection (WebInputStream::Listener* listener, const int numRedirects)
    {
        closeSocket (false);

        if (isPost)
            WebInputStream::createHeadersAndPostData (url, headers, postData);

        uint32 timeOutTime = Time::getMillisecondCounter();

        if (timeOutMs == 0)
            timeOutMs = 30000;

        if (timeOutMs < 0)
            timeOutTime = 0xffffffff;
        else
            timeOutTime += (uint32) timeOutMs;

        String hostName, hostPath;
        int hostPort;
        if (! decomposeURL (address, hostName, hostPath, hostPort))
            return 0;

        String serverName, proxyName, proxyPath;
        int proxyPort = 0;
        int port = 0;

        const String proxyURL (getenv ("http_proxy"));
        if (proxyURL.startsWithIgnoreCase ("http://"))
        {
            if (! decomposeURL (proxyURL, proxyName, proxyPath, proxyPort))
                return 0;

            serverName = proxyName;
            port = proxyPort;
        }
        else
        {
            serverName = hostName;
            port = hostPort;
        }

        struct addrinfo hints;
        zerostruct (hints);

        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_NUMERICSERV;

        struct addrinfo* result = nullptr;
        if (getaddrinfo (serverName.toUTF8(), String (port).toUTF8(), &hints, &result) != 0 || result == 0)
            return 0;

        socketHandle = socket (result->ai_family, result->ai_socktype, 0);

        if (socketHandle == -1)
        {
            freeaddrinfo (result);
            return 0;
        }

        int receiveBufferSize = 16384;
        setsockopt (socketHandle, SOL_SOCKET, SO_RCVBUF, (char*) &receiveBufferSize, sizeof (receiveBufferSize));
        setsockopt (socketHandle, SOL_SOCKET, SO_KEEPALIVE, 0, 0);

      #if JUCE_MAC
        setsockopt (socketHandle, SOL_SOCKET, SO_NOSIGPIPE, 0, 0);
      #endif

        if (::connect (socketHandle, result->ai_addr, result->ai_addrlen) == -1)
        {
            closeSocket();
            freeaddrinfo (result);
            return 0;
        }

        freeaddrinfo (result);

        {
            const MemoryBlock requestHeader (createRequestHeader (hostName, hostPort, proxyName, proxyPort, hostPath,
                                                                  address, headers, postData, isPost, httpRequestCmd));

            if (! sendHeader (socketHandle, requestHeader, timeOutTime, owner, listener))
            {
                closeSocket();
                return 0;
            }
        }

        String responseHeader (readResponse (timeOutTime));
        position = 0;

        if (responseHeader.isNotEmpty())
        {
            headerLines = StringArray::fromLines (responseHeader);

            const int status = responseHeader.fromFirstOccurrenceOf (" ", false, false)
                                             .substring (0, 3).getIntValue();

            String location (findHeaderItem (headerLines, "Location:"));

            if (++levelsOfRedirection <= numRedirects
                 && status >= 300 && status < 400
                 && location.isNotEmpty() && location != address)
            {
                if (! (location.startsWithIgnoreCase ("http://")
                        || location.startsWithIgnoreCase ("https://")
                        || location.startsWithIgnoreCase ("ftp://")))
                {
                    // The following is a bit dodgy. Ideally, we should do a proper transform of the relative URI to a target URI
                    if (location.startsWithChar ('/'))
                        location = URL (address).withNewSubPath (location).toString (true);
                    else
                        location = address + "/" + location;
                }

                address = location;
                return createConnection (listener, numRedirects);
            }

            String contentLengthString (findHeaderItem (headerLines, "Content-Length:"));

            if (contentLengthString.isNotEmpty())
                contentLength = contentLengthString.getLargeIntValue();

            isChunked = (findHeaderItem (headerLines, "Transfer-Encoding:") == "chunked");

            return status;
        }

        closeSocket();
        return 0;
    }

    //==============================================================================
    String readResponse (const uint32 timeOutTime)
    {
        int numConsecutiveLFs  = 0;
        MemoryOutputStream buffer;

        while (numConsecutiveLFs < 2
                && buffer.getDataSize() < 32768
                && Time::getMillisecondCounter() <= timeOutTime
                && ! (finished || isError()))
        {
            char c = 0;
            if (read (&c, 1) != 1)
                return String();

            buffer.writeByte (c);

            if (c == '\n')
                ++numConsecutiveLFs;
            else if (c != '\r')
                numConsecutiveLFs = 0;
        }

        const String header (buffer.toString().trimEnd());

        if (header.startsWithIgnoreCase ("HTTP/"))
            return header;

        return String();
    }

    static void writeValueIfNotPresent (MemoryOutputStream& dest, const String& headers, const String& key, const String& value)
    {
        if (! headers.containsIgnoreCase (key))
            dest << "\r\n" << key << ' ' << value;
    }

    static void writeHost (MemoryOutputStream& dest, const String& httpRequestCmd,
                           const String& path, const String& host, int port)
    {
        dest << httpRequestCmd << ' ' << path << " HTTP/1.1\r\nHost: " << host;

        /* HTTP spec 14.23 says that the port number must be included in the header if it is not 80 */
        if (port != 80)
            dest << ':' << port;
    }

    static MemoryBlock createRequestHeader (const String& hostName, const int hostPort,
                                            const String& proxyName, const int proxyPort,
                                            const String& hostPath, const String& originalURL,
                                            const String& userHeaders, const MemoryBlock& postData,
                                            const bool isPost, const String& httpRequestCmd)
    {
        MemoryOutputStream header;

        if (proxyName.isEmpty())
            writeHost (header, httpRequestCmd, hostPath, hostName, hostPort);
        else
            writeHost (header, httpRequestCmd, originalURL, proxyName, proxyPort);

        writeValueIfNotPresent (header, userHeaders, "User-Agent:", "JUCE/" JUCE_STRINGIFY(JUCE_MAJOR_VERSION)
                                                                        "." JUCE_STRINGIFY(JUCE_MINOR_VERSION)
                                                                        "." JUCE_STRINGIFY(JUCE_BUILDNUMBER));
        writeValueIfNotPresent (header, userHeaders, "Connection:", "close");

        if (isPost)
            writeValueIfNotPresent (header, userHeaders, "Content-Length:", String ((int) postData.getSize()));

        if (userHeaders.isNotEmpty())
            header << "\r\n" << userHeaders;

        header << "\r\n";

        if (isPost)
            header << postData;

        return header.getMemoryBlock();
    }

    static bool sendHeader (int socketHandle, const MemoryBlock& requestHeader, const uint32 timeOutTime,
                            WebInputStream& pimplOwner, WebInputStream::Listener* listener)
    {
        size_t totalHeaderSent = 0;

        while (totalHeaderSent < requestHeader.getSize())
        {
            if (Time::getMillisecondCounter() > timeOutTime)
                return false;

            const int numToSend = jmin (1024, (int) (requestHeader.getSize() - totalHeaderSent));

            if (send (socketHandle, static_cast<const char*> (requestHeader.getData()) + totalHeaderSent, (size_t) numToSend, 0) != numToSend)
                return false;

            totalHeaderSent += (size_t) numToSend;

            if (listener != nullptr && ! listener->postDataSendProgress (pimplOwner, (int) totalHeaderSent, (int) requestHeader.getSize()))
                return false;
        }

        return true;
    }

    static bool decomposeURL (const String& url, String& host, String& path, int& port)
    {
        if (! url.startsWithIgnoreCase ("http://"))
            return false;

        const int nextSlash = url.indexOfChar (7, '/');
        int nextColon = url.indexOfChar (7, ':');
        if (nextColon > nextSlash && nextSlash > 0)
            nextColon = -1;

        if (nextColon >= 0)
        {
            host = url.substring (7, nextColon);

            if (nextSlash >= 0)
                port = url.substring (nextColon + 1, nextSlash).getIntValue();
            else
                port = url.substring (nextColon + 1).getIntValue();
        }
        else
        {
            port = 80;

            if (nextSlash >= 0)
                host = url.substring (7, nextSlash);
            else
                host = url.substring (7);
        }

        if (nextSlash >= 0)
            path = url.substring (nextSlash);
        else
            path = "/";

        return true;
    }

    static String findHeaderItem (const StringArray& lines, const String& itemName)
    {
        for (int i = 0; i < lines.size(); ++i)
            if (lines[i].startsWithIgnoreCase (itemName))
                return lines[i].substring (itemName.length()).trim();

        return String();
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Pimpl)
};

URL::DownloadTask* URL::downloadToFile (const File& targetLocation, String extraHeaders, DownloadTask::Listener* listener)
{
    return URL::DownloadTask::createFallbackDownloader (*this, targetLocation, extraHeaders, listener);
}
#endif
