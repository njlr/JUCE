/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-7 by Raw Material Software ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the
   GNU General Public License, as published by the Free Software Foundation;
   either version 2 of the License, or (at your option) any later version.

   JUCE is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with JUCE; if not, visit www.gnu.org/licenses or write to the
   Free Software Foundation, Inc., 59 Temple Place, Suite 330,
   Boston, MA 02111-1307 USA

  ------------------------------------------------------------------------------

   If you'd like to release a closed-source product which uses JUCE, commercial
   licenses are also available: visit www.rawmaterialsoftware.com/juce for
   more information.

  ==============================================================================
*/

#ifndef __JUCE_AUDIOTRANSPORTSOURCE_JUCEHEADER__
#define __JUCE_AUDIOTRANSPORTSOURCE_JUCEHEADER__

#include "juce_BufferingAudioSource.h"
#include "juce_ResamplingAudioSource.h"
#include "../../events/juce_ChangeBroadcaster.h"


//==============================================================================
/**
    An AudioSource that takes a PositionableAudioSource and allows it to be
    played, stopped, started, etc.

    This can also be told use a buffer and background thread to read ahead, and
    if can correct for different sample-rates.

    You may want to use one of these along with an AudioSourcePlayer and AudioIODevice
    to control playback of an audio file.

    @see AudioSource, AudioSourcePlayer
*/
class JUCE_API  AudioTransportSource  : public PositionableAudioSource,
                                        public ChangeBroadcaster
{
public:
    //==============================================================================
    /** Creates an AudioTransportSource.

        After creating one of these, use the setSource() method to select an input source.
    */
    AudioTransportSource();

    /** Destructor. */
    ~AudioTransportSource();

    //==============================================================================
    /** Sets the reader that is being used as the input source.

        This will stop playback, reset the position to 0 and change to the new reader.

        The source passed in will not be deleted by this object, so must be managed by
        the caller.

        @param newSource                        the new input source to use. This may be zero
        @param readAheadBufferSize              a size of buffer to use for reading ahead. If this
                                                is zero, no reading ahead will be done; if it's
                                                greater than zero, a BufferingAudioSource will be used
                                                to do the reading-ahead
        @param sourceSampleRateToCorrectFor     if this is non-zero, it specifies the sample
                                                rate of the source, and playback will be sample-rate
                                                adjusted to maintain playback at the correct pitch. If
                                                this is 0, no sample-rate adjustment will be performed
    */
    void setSource (PositionableAudioSource* const newSource,
                    int readAheadBufferSize = 0,
                    double sourceSampleRateToCorrectFor = 0.0);

    //==============================================================================
    /** Changes the current playback position in the source stream.

        The next time the getNextAudioBlock() method is called, this
        is the time from which it'll read data.

        @see getPosition
    */
    void setPosition (double newPosition);

    /** Returns the position that the next data block will be read from

        This is a time in seconds.
    */
    double getCurrentPosition() const;

    /** Returns true if the player has stopped because its input stream ran out of data.
    */
    bool hasStreamFinished() const throw()              { return inputStreamEOF; }

    //==============================================================================
    /** Starts playing (if a source has been selected).

        If it starts playing, this will send a message to any ChangeListeners
        that are registered with this object.
    */
    void start();

    /** Stops playing.

        If it's actually playing, this will send a message to any ChangeListeners
        that are registered with this object.
    */
    void stop();

    /** Returns true if it's currently playing. */
    bool isPlaying() const throw()      { return playing; }

    //==============================================================================
    /** Changes the gain to apply to the output.

        @param newGain  a factor by which to multiply the outgoing samples,
                        so 1.0 = 0dB, 0.5 = -6dB, 2.0 = 6dB, etc.
    */
    void setGain (const float newGain) throw();

    /** Returns the current gain setting.

        @see setGain
    */
    float getGain() const throw()       { return gain; }


    //==============================================================================
    /** Implementation of the AudioSource method. */
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate);

    /** Implementation of the AudioSource method. */
    void releaseResources();

    /** Implementation of the AudioSource method. */
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill);

    //==============================================================================
    /** Implements the PositionableAudioSource method. */
    void setNextReadPosition (int newPosition);

    /** Implements the PositionableAudioSource method. */
    int getNextReadPosition() const;

    /** Implements the PositionableAudioSource method. */
    int getTotalLength() const;

    /** Implements the PositionableAudioSource method. */
    bool isLooping() const;

    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    PositionableAudioSource* source;
    ResamplingAudioSource* resamplerSource;
    BufferingAudioSource* bufferingSource;
    PositionableAudioSource* positionableSource;
    AudioSource* masterSource;

    CriticalSection callbackLock;
    float volatile gain, lastGain;
    bool volatile playing, stopped;
    double sampleRate, sourceSampleRate;
    int blockSize, readAheadBufferSize;
    bool isPrepared, inputStreamEOF;

    AudioTransportSource (const AudioTransportSource&);
    const AudioTransportSource& operator= (const AudioTransportSource&);
};


#endif   // __JUCE_AUDIOTRANSPORTSOURCE_JUCEHEADER__
