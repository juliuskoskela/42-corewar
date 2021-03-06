#ifndef CONFIG_H
# define CONFIG_H

///////////////////////////////////////////////////////////////////////////////
///
/// \brief Configurable macros. User can change these to alter behavior.
///
/// \authors Julius Koskela
///
///////////////////////////////////////////////////////////////////////////////

/// System ////////////////////////////////////////////////////////////////////

# define CR_ACTIVE 1
# define CR_STACK_TRACE_MAX 1024
# define CR_TRACK_ALLOC 1
# define CR_TRACK_ALLOC_BACKTRACE 1
# define CR_TRACK_ERROR 1
# define CR_TRACK_ERROR_BACKTRACE 1
# define CR_RECOVERY_POLICY 0

/// Map ///////////////////////////////////////////////////////////////////////

# define CR_MAP_START_CAPACITY 1000
# define CR_MAP_LOAD_FACTOR 0.4

///////////////////////////////////////////////////////////////////////////////

#endif
