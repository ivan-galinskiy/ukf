/* Selects the floating-point precision to use. */
#if !(defined(UKF_DOUBLE_PRECISION) ^ defined(UKF_SINGLE_PRECISION))
#  error "Define exactly one of UKF_DOUBLE_PRECISION or UKF_SINGLE_PRECISION"
#endif

#if defined(UKF_DOUBLE_PRECISION)
using real_t = double;
#else
using real_t = float;
#endif
