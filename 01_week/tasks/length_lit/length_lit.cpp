constexpr long double METER_IN_FOOT = 0.3048;
constexpr long double INCH_IN_FOOT = 12;
constexpr long double METER_IN_INCH = 0.0254;

constexpr long double operator""_ft_to_m(long double foot) {
    return foot * METER_IN_FOOT;
}

constexpr long double operator""_m_to_ft(long double meter) {
    return meter / METER_IN_FOOT;
}

constexpr long double operator""_ft_to_cm(long double foot) {
    return foot * METER_IN_FOOT * 100;
}

constexpr long double operator""_cm_to_ft(long double cm) {
    return cm / (METER_IN_FOOT * 100);
}

constexpr long double operator""_ft_to_in(long double foot) {
    return foot * INCH_IN_FOOT;
}

constexpr long double operator""_in_to_ft(long double inch) {
    return inch / INCH_IN_FOOT;
}

constexpr long double operator""_in_to_m(long double inch) {
    return inch * METER_IN_INCH;
}

constexpr long double operator""_m_to_in(long double meter) {
    return meter / METER_IN_INCH;
}

constexpr long double operator""_in_to_cm(long double inch) {
    return inch * METER_IN_INCH * 100;
}

constexpr long double operator""_cm_to_in(long double inch) {
    return inch / (METER_IN_INCH * 100);
}

constexpr long double operator""_m_to_cm(long double meter) {
    return meter * 100;
}

constexpr long double operator""_cm_to_m(long double cm) {
    return cm / 100;
}
