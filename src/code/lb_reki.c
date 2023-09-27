#include "lb_reki.h"
#include "attributes.h"

lbRTC_day_t t_seiyo_days_tbl[2][lbRTC_MONTHS_MAX + 1] = {
    { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }, /* Standard days for each month */
    { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }, /* Days for each month during leap year */
};

// clang-format off
lbRekiPhase l_lbRk_ConvertTable[lbRk_YEAR_NUM][lbRk_KYUU_LEAP_MONTH] = {
  /* 2000 */ {{2,  5}, {3,  6}, {4,  5}, {5,  4}, {6,  2}, {7,  2}, {7, 31}, {8, 29}, { 9, 28}, {10, 27}, {11, 26}, {12, 26}, { 0,  0}},
  /* 2001 */ {{1, 24}, {2, 23}, {3, 25}, {4, 24}, {6, 21}, {7, 21}, {8, 19}, {9, 17}, {10, 17}, {11, 15}, {12, 15}, { 1, 13}, { 5, 23}},
  /* 2002 */ {{2, 12}, {3, 14}, {4, 13}, {5, 12}, {6, 11}, {7, 10}, {8,  9}, {9,  7}, {10,  6}, {11,  5}, {12,  4}, { 1,  3}, { 0,  0}},
  /* 2003 */ {{2,  1}, {3,  3}, {4,  2}, {5,  1}, {5, 31}, {6, 30}, {7, 29}, {8, 28}, { 9, 29}, {10, 25}, {11, 24}, {12, 23}, { 0,  0}},
  /* 2004 */ {{1, 22}, {2, 20}, {4, 19}, {5, 19}, {6, 18}, {7, 17}, {8, 16}, {9, 14}, {10, 14}, {11, 12}, {12, 12}, { 1, 10}, { 3, 21}},
  /* 2005 */ {{2,  9}, {3, 10}, {4,  9}, {5,  8}, {6,  7}, {7,  6}, {8,  5}, {9,  4}, {10,  3}, {11,  2}, {12,  2}, {12, 31}, { 0,  0}},
  /* 2006 */ {{1, 29}, {2, 28}, {3, 29}, {4, 28}, {5, 27}, {6, 26}, {7, 25}, {9, 22}, {10, 22}, {11, 21}, {12, 20}, { 1, 19}, { 8, 24}},
  /* 2007 */ {{2, 18}, {3, 19}, {4, 17}, {5, 17}, {6, 15}, {7, 14}, {8, 13}, {9, 11}, {10, 11}, {11, 10}, {12, 10}, { 1,  8}, { 0,  0}},
  /* 2008 */ {{2,  7}, {3,  8}, {4,  6}, {5,  5}, {6,  4}, {7,  3}, {8,  1}, {8, 31}, { 9, 29}, {10, 29}, {11, 28}, {12, 27}, { 0,  0}},
  /* 2009 */ {{1, 26}, {2, 25}, {3, 27}, {4, 25}, {5, 24}, {7, 22}, {8, 20}, {9, 19}, {10, 18}, {11, 17}, {12, 16}, { 1, 15}, { 6, 23}},
  /* 2010 */ {{2, 14}, {3, 16}, {4, 14}, {5, 14}, {6, 12}, {7, 12}, {8, 10}, {9,  8}, {10,  8}, {11,  6}, {12,  6}, { 1,  4}, { 0,  0}},
  /* 2011 */ {{2,  3}, {3,  5}, {4,  3}, {5,  3}, {6,  2}, {7,  1}, {7, 31}, {8, 29}, { 9, 27}, {10, 27}, {11, 25}, {12, 25}, { 0,  0}},
  /* 2012 */ {{1, 23}, {2, 22}, {3, 22}, {5, 21}, {6, 20}, {7, 19}, {8, 18}, {9, 16}, {10, 15}, {11, 14}, {12, 13}, { 1, 12}, { 4, 21}},
  /* 2013 */ {{2, 10}, {3, 12}, {4, 10}, {5, 10}, {6,  9}, {7,  8}, {8,  7}, {9,  5}, {10,  5}, {11,  3}, {12,  3}, { 1,  1}, { 0,  0}},
  /* 2014 */ {{1, 31}, {3,  1}, {3, 31}, {4, 29}, {5, 29}, {6, 27}, {7, 27}, {8, 25}, { 9, 24}, {11, 22}, {12, 22}, { 1, 20}, {10, 24}},
  /* 2015 */ {{2, 19}, {3, 20}, {4, 19}, {5, 18}, {6, 16}, {7, 16}, {8, 14}, {9, 13}, {10, 13}, {11, 12}, {12, 11}, { 1, 10}, { 0,  0}},
  /* 2016 */ {{2,  8}, {3,  9}, {4,  7}, {5,  7}, {6,  5}, {7,  4}, {8,  3}, {9,  1}, {10,  1}, {10, 31}, {11, 29}, {12, 29}, { 0,  0}},
  /* 2017 */ {{1, 28}, {2, 26}, {3, 28}, {4, 26}, {5, 26}, {7, 23}, {8, 22}, {9, 20}, {10, 20}, {11, 18}, {12, 18}, { 1, 17}, { 6, 24}},
  /* 2018 */ {{2, 16}, {3, 17}, {4, 16}, {5, 15}, {6, 14}, {7, 13}, {8, 11}, {9, 10}, {10,  9}, {11,  8}, {12, 27}, { 1,  6}, { 0,  0}},
  /* 2019 */ {{2,  5}, {3,  7}, {4,  5}, {5,  5}, {6,  3}, {7,  3}, {8,  1}, {8, 30}, { 9, 29}, {10, 28}, {11, 27}, {12, 26}, { 0,  0}},
  /* 2020 */ {{1, 25}, {2, 24}, {3, 24}, {4, 23}, {6, 21}, {7, 21}, {8, 19}, {9, 17}, {10, 17}, {11, 15}, {12, 15}, { 1, 13}, { 5, 23}},
  /* 2021 */ {{2, 12}, {3, 13}, {4, 12}, {5, 12}, {6, 10}, {7, 10}, {8,  8}, {9,  7}, {10,  6}, {11,  5}, {12,  4}, { 1,  3}, { 0,  0}},
  /* 2022 */ {{2,  1}, {3,  3}, {4,  1}, {5,  1}, {5, 30}, {6, 29}, {7, 29}, {8, 27}, { 9, 26}, {10, 25}, {11, 24}, {12, 23}, { 0,  0}},
  /* 2023 */ {{1, 22}, {2, 20}, {3, 22}, {5, 20}, {6, 18}, {7, 18}, {8, 16}, {9, 15}, {10, 15}, {11, 13}, {12, 13}, { 1, 11}, { 4, 20}},
  /* 2024 */ {{2, 10}, {3, 10}, {4,  9}, {5,  8}, {6,  6}, {7,  6}, {8,  4}, {9,  3}, {10,  3}, {11,  1}, {12,  1}, {12, 31}, { 0,  0}},
  /* 2025 */ {{1, 29}, {2, 28}, {3, 29}, {4, 28}, {5, 27}, {6, 25}, {8, 23}, {9, 22}, {10, 21}, {11, 20}, {12, 20}, { 1, 19}, { 7, 25}},
  /* 2026 */ {{2, 17}, {3, 19}, {4, 17}, {5, 17}, {6, 15}, {7, 14}, {8, 13}, {9, 11}, {10, 11}, {11,  9}, {12,  9}, { 1,  8}, { 0,  0}},
  /* 2027 */ {{2,  7}, {3,  8}, {4,  7}, {5,  6}, {6,  5}, {7,  4}, {8,  2}, {9,  1}, { 9, 30}, {10, 29}, {11, 28}, {12, 28}, { 0,  0}},
  /* 2028 */ {{1, 27}, {2, 25}, {3, 26}, {4, 25}, {5, 24}, {7, 22}, {8, 20}, {9, 19}, {10, 18}, {11, 16}, {12, 16}, { 1, 15}, { 6, 23}},
  /* 2029 */ {{2, 13}, {3, 15}, {4, 14}, {5, 13}, {6, 12}, {7, 12}, {8, 10}, {9,  8}, {10,  8}, {11,  6}, {12,  5}, { 1,  4}, { 0,  0}},
  /* 2030 */ {{2,  3}, {3,  4}, {4,  3}, {5,  2}, {6,  1}, {7,  1}, {7, 30}, {8, 29}, { 9, 27}, {10, 27}, {11, 25}, {12, 25}, { 0,  0}},
  /* 2031 */ {{1, 23}, {2, 22}, {3, 23}, {4, 22}, {6, 20}, {7, 19}, {8, 18}, {9, 17}, {10, 16}, {11, 15}, {12, 14}, { 1, 13}, { 5, 21}},
  /* 2032 */ {{2, 11}, {3, 12}, {4, 10}, {5,  9}, {6,  8}, {7,  7}, {8,  6}, {9,  5}, {10,  4}, {11,  3}, {12,  3}, { 1,  1}, { 0,  0}},
};
// clang-format on

s32 l_lbRk_leapdays[lbRk_YEAR_NUM] = {
    0, 29, 0, 0, 29, 0, 29, 0, 0, 29, 0, 0, 30, 0, 29, 0, 0, 29, 0, 0, 29, 0, 0, 30, 0, 29, 0, 0, 29, 0, 0, 30, 0,
};

s32 lbRk_SeirekiDays(s32 year, s32 month) {
    s32 idx = 0;

    if ((year % 4) == 0) {
        idx = 1;
    }

    return t_seiyo_days_tbl[idx][month];
}

lbRekiPhase* lbRk_ToSeiyoMonthAndDay(s32 year, s32 month) {
    return &l_lbRk_ConvertTable[year - lbRk_YEAR_MIN][month - 1];
}

s32 lbRk_KyuurekiLeapDays(s32 year) {
    return l_lbRk_leapdays[year - lbRk_YEAR_MIN];
}

s32 lbRk_IsKyuurekiLeapYear(s32 year) {
    if (l_lbRk_leapdays[year - lbRk_YEAR_MIN] != 0) {
        return 1;
    };

    return 0;
}

s32 lbRk_IsLeapMonth(s32 month) {
    if (month == lbRk_KYUU_LEAP_MONTH) {
        return 1;
    }

    return 0;
}

s32 lbRk_IsLeapOnNextMonth(s32 year, s32 month) {
    if ((lbRk_ToSeiyoMonthAndDay(year, month)->month + 1) ==
        (l_lbRk_ConvertTable[year - lbRk_YEAR_MIN][lbRTC_MONTHS_MAX].month)) {
        return 1;
    }
    return 0;
}

s32 lbRk_KyuurekiDays(s32 year, s32 month) {
    lbRekiPhase* seiyoDay;
    lbRekiPhase* nextSeiyo;
    s32 days;

    seiyoDay = lbRk_ToSeiyoMonthAndDay(year, month);

    if (lbRk_IsLeapMonth(month) == TRUE) {
        return lbRk_KyuurekiLeapDays(year);
    }

    if (month != lbRTC_MONTHS_MAX) {
        if (lbRk_IsLeapOnNextMonth(year, month) == TRUE) {
            nextSeiyo = lbRk_ToSeiyoMonthAndDay(year, lbRk_KYUU_LEAP_MONTH);
        } else {
            nextSeiyo = lbRk_ToSeiyoMonthAndDay(year, month + 1);
        }
    } else {
        nextSeiyo = lbRk_ToSeiyoMonthAndDay(year + 1, 1);
    }

    if (seiyoDay->month == nextSeiyo->month) {
        days = nextSeiyo->day - seiyoDay->day;
    } else {
        if (seiyoDay->month < month) {
            year += 1;
        }
        days = lbRk_SeirekiDays(year, seiyoDay->month) - seiyoDay->day;
        if ((nextSeiyo->month - seiyoDay->month) >= 2) {
            days += lbRk_SeirekiDays(year, seiyoDay->month + 1);
        }
        days += nextSeiyo->day;
    }
    return days;
}

s32 lbRk_ToSeiyouReki(lbRTC_ymd_t* seiyoTime, const lbRTC_ymd_t* kyuuTime) {
    s32 pad UNUSED;
    s32 rekiDays;
    s32 year;
    s32 month;
    s32 day;
    lbRekiPhase* seiyoDay;

    if ((kyuuTime->year < 1) || (kyuuTime->year > lbRk_YEAR_MAX)) {
        return FALSE;
    }
    if (kyuuTime->month > lbRk_KYUU_LEAP_MONTH) {
        return FALSE;
    }
    if (lbRk_IsKyuurekiLeapYear(kyuuTime->year) == FALSE && kyuuTime->month >= lbRk_KYUU_LEAP_MONTH) {
        return FALSE;
    }
    if (lbRk_KyuurekiDays(kyuuTime->year, kyuuTime->month) < kyuuTime->day) {
        return FALSE;
    }

    seiyoDay = lbRk_ToSeiyoMonthAndDay(kyuuTime->year, kyuuTime->month);

    year = kyuuTime->year;
    month = seiyoDay->month;
    day = seiyoDay->day + kyuuTime->day - 1;

    rekiDays = lbRk_SeirekiDays(year, month);

    if (day > rekiDays) {
        month++;
        day -= rekiDays;
        if (month > lbRTC_MONTHS_MAX) {
            month = 1;
        }
    }

    if (month < kyuuTime->month && kyuuTime->month != lbRk_KYUU_LEAP_MONTH) {
        year++;
    }

    seiyoTime->year = year;
    seiyoTime->month = month;
    seiyoTime->day = day;

    return TRUE;
}

s32 lbRk_ToKyuuReki(lbRTC_ymd_t* kyuuTime, const lbRTC_ymd_t* seiyoTime) {
    lbRTC_ymd_t kyuuDate = { lbRk_YEAR_MIN, lbRk_KYUU_MONTH_START, lbRk_KYUU_DAY_START };
    lbRTC_ymd_t seyioDate;

    while (TRUE) {

        if (lbRk_ToSeiyouReki(&seyioDate, &kyuuDate) == FALSE) {
            return FALSE;
        }

        if (seyioDate.day == seiyoTime->day && seyioDate.month == seiyoTime->month &&
            seyioDate.year == seiyoTime->year) {
            kyuuTime->day = kyuuDate.day;
            kyuuTime->month = kyuuDate.month;
            kyuuTime->year = kyuuDate.year;
            return TRUE;
        }

        kyuuDate.day++;

        if (lbRk_KyuurekiDays(kyuuDate.year, kyuuDate.month) < kyuuDate.day) {
            kyuuDate.day = 1;
            kyuuDate.month++;

            if (lbRk_IsKyuurekiLeapYear(kyuuDate.year) == FALSE) {
                if (kyuuDate.month > lbRk_KYUU_MONTH_END) {
                    kyuuDate.month = 1;
                    kyuuDate.year++;
                    if (kyuuDate.year > lbRk_YEAR_MAX) {
                        return FALSE;
                    }
                }
            } else if (kyuuDate.month > lbRk_KYUU_LEAP_MONTH) {
                kyuuDate.month = 1;
                kyuuDate.year++;
                if (kyuuDate.year > lbRk_YEAR_MAX) {
                    return FALSE;
                }
            }
        }
    }
}
