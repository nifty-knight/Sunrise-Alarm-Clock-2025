#ifndef _MOCK_DS_1302_H
#define _MOCK_DS_1302_H

#include <stdint.h>

class Ds1302
{
    public:

        typedef struct {
            uint8_t year;
            uint8_t month;
            uint8_t day;
            uint8_t hour;
            uint8_t minute;
            uint8_t second;
            uint8_t dow;
        } DateTime;

        /**
         * Months of year
         */
        enum MONTH : uint8_t {
            MONTH_JAN = 1,
            MONTH_FEB = 2,
            MONTH_MAR = 3,
            MONTH_APR = 4,
            MONTH_MAY = 5,
            MONTH_JUN = 6,
            MONTH_JUL = 7,
            MONTH_AUG = 8,
            MONTH_SEP = 9,
            MONTH_OCT = 10,
            MONTH_NOV = 11,
            MONTH_DEC = 12
        };

        /**
         * Days of week
         */
        enum DOW : uint8_t {
            DOW_MON = 1,
            DOW_TUE = 2,
            DOW_WED = 3,
            DOW_THU = 4,
            DOW_FRI = 5,
            DOW_SAT = 6,
            DOW_SUN = 7
        };

        /**
         * Constructor (pin configuration).
         */
        Ds1302(uint8_t pin_ena, uint8_t pin_clk, uint8_t pin_dat);

    private:

        uint8_t _pin_ena;
        uint8_t _pin_clk;
        uint8_t _pin_dat;
};

#endif // _DS_1302_H