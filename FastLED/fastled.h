#ifndef __INC_FASTSPI_LED2_H
#define __INC_FASTSPI_LED2_H

#ifndef __PROG_TYPES_COMPAT__
#define __PROG_TYPES_COMPAT__
#endif

#ifdef SmartMatrix_h
#include <SmartMatrix.h>
#endif

#ifdef DmxSimple_h
#include <DmxSimple.h>
#endif

#ifdef DmxSerial_h
#include <DMXSerial.h>
#endif

#include <stdint.h>

#include "fastled_config.h"

// Utility functions

#include "controller.h"
//#include "fastspi_types.h"

#include "lib8tion.h"
#include "pixeltypes.h"
//#include "hsv2rgb.h"
//#include "colorutils.h"
//#include "pixelset.h"
//#include "colorpalettes.h"

//#include "noise.h"
//#include "power_mgt.h"


typedef uint8_t (*power_func)(uint8_t scale, uint32_t data);


class CFastLED
{
    uint8_t  m_Scale; 			///< The current global brightness scale setting
    uint16_t m_nFPS;			///< Tracking for current FPS value
    uint32_t m_nMinMicros;		///< minimum µs between frames, used for capping frame rates.
    uint32_t m_nPowerData;		///< max power use parameter
    power_func m_pPowerFunc;	///< function for overriding brightness when using FastLED.show();
public:
    CFastLED();

    /// Add a CLEDController instance to the world.  Exposed to the public to allow people to implement their own
    /// CLEDController objects or instances.  There are two ways to call this method (as well as the other addLeds)
    /// variations.  The first is with 3 arguments, in which case the arguments are the controller, a pointer to
    /// led data, and the number of leds used by this controller.  The second is with 4 arguments, in which case
    /// the first two arguments are the same, the third argument is an offset into the CRGB data where this controller's
    /// CRGB data begins, and the fourth argument is the number of leds for this controller object.
    /// @param pLed - the led controller being added
    /// @param data - base point to an array of CRGB data structures
    /// @param nLedsOrOffset - number of leds (3 argument version) or offset into the data array
    /// @param nLedsIfOffset - number of leds (4 argument version)
    /// @returns a reference to the added controller
    static CLEDController &addLeds(struct CRGB *data, int nLedsOrOffset, int nLedsIfOffset = 0);

    /// Set the global brightness scaling
    /// @param scale a 0-255 value for how much to scale all leds before writing them out
    void setBrightness(uint8_t scale) { m_Scale = scale; }

    /// Get the current global brightness setting
    /// @returns the current global brightness value
    uint8_t getBrightness() { return m_Scale; }

    /// Set the maximum power to be used, given in volts and milliamps.
    /// @param volts - how many volts the leds are being driven at (usually 5)
    /// @param milliamps - the maximum milliamps of power draw you want
    //inline void setMaxPowerInVoltsAndMilliamps(uint8_t volts, uint32_t milliamps) { setMaxPowerInMilliWatts(volts * milliamps); }

    /// Set the maximum power to be used, given in milliwatts
    /// @param milliwatts - the max power draw desired, in milliwatts
    //inline void setMaxPowerInMilliWatts(uint32_t milliwatts) { m_pPowerFunc = &calculate_max_brightness_for_power_mW; m_nPowerData = milliwatts; }

    /// Update all our controllers with the current led colors, using the passed in brightness
    /// @param scale temporarily override the scale
    void show(uint8_t scale);

    /// Update all our controllers with the current led colors
    void show() { show(m_Scale); }

    /// clear the leds, wiping the local array of data, optionally black out the leds as well
    /// @param writeData whether or not to write out to the leds as well
    void clear(bool writeData = false);

    /// clear out the local data array
    void clearData();

    /// Set all leds on all controllers to the given color/scale
    /// @param color what color to set the leds to
    /// @param scale what brightness scale to show at
    void showColor(const struct CRGB & color, uint8_t scale);

    /// Set all leds on all controllers to the given color
    /// @param color what color to set the leds to
    void showColor(const struct CRGB & color) { showColor(color, m_Scale); }

    /// Delay for the given number of milliseconds.  Provided to allow the library to be used on platforms
    /// that don't have a delay function (to allow code to be more portable).  Note: this will call show
    /// constantly to drive the dithering engine (and will call show at least once).
    /// @param ms the number of milliseconds to pause for
    void delay(unsigned long ms);

    /// Set a global color temperature.  Sets the color temperature for all added led strips, overriding whatever
    /// previous color temperature those controllers may have had
    /// @param temp A CRGB structure describing the color temperature
    void setTemperature(const struct CRGB & temp);

    /// Set a global color correction.  Sets the color correction for all added led strips,
    /// overriding whatever previous color correction those controllers may have had.
    /// @param correction A CRGB structure describin the color correction.
    void setCorrection(const struct CRGB & correction);

    /// Set the dithering mode.  Sets the dithering mode for all added led strips, overriding
    /// whatever previous dithering option those controllers may have had.
    /// @param ditherMode - what type of dithering to use, either BINARY_DITHER or DISABLE_DITHER
    void setDither(uint8_t ditherMode = BINARY_DITHER);

    /// Set the maximum refresh rate.  This is global for all leds.  Attempts to
    /// call show faster than this rate will simply wait.  Note that the refresh rate
    /// defaults to the slowest refresh rate of all the leds added through addLeds.  If
    /// you wish to set/override this rate, be sure to call setMaxRefreshRate _after_
    /// adding all of your leds.
    /// @param refresh - maximum refresh rate in hz
    /// @param constrain - constrain refresh rate to the slowest speed yet set
    void setMaxRefreshRate(uint16_t refresh, bool constrain=false);

    /// for debugging, will keep track of time between calls to countFPS, and every
    /// nFrames calls, it will update an internal counter for the current FPS.
    /// @todo make this a rolling counter
    /// @param nFrames - how many frames to time for determining FPS
    void countFPS(int nFrames=25);

    /// Get the number of frames/second being written out
    /// @returns the most recently computed FPS value
    uint16_t getFPS() { return m_nFPS; }

    /// Get how many controllers have been registered
    /// @returns the number of controllers (strips) that have been added with addLeds
    int count();

    /// Get a reference to a registered controller
    /// @returns a reference to the Nth controller
    CLEDController & operator[](int x);

    /// Get the number of leds in the first controller
    /// @returns the number of LEDs in the first controller
    int size() { return (*this)[0].size(); }

    /// Get a pointer to led data for the first controller
    /// @returns pointer to the CRGB buffer for the first controller
    CRGB *leds() { return (*this)[0].leds(); }
};

#define FastSPI_LED FastLED
#define FastSPI_LED2 FastLED
#ifndef LEDS
#   define LEDS FastLED
#endif

extern CFastLED FastLED;

#endif // FASTLED_H
