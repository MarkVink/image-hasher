// Configure verbosity of output messages.
//
// Define 'cimg_verbosity' to: '0' to hide library messages (quiet mode).
//                             '1' to output library messages on the console.
//                             '2' to output library messages on a basic dialog window (default behavior).
//                             '3' to do as '1' + add extra warnings (may slow down the code!).
//                             '4' to do as '2' + add extra warnings (may slow down the code!).
//
// Define 'cimg_strict_warnings' to replace warning messages by exception throwns.
//
// Define 'cimg_use_vt100' to allow output of color messages on VT100-compatible terminals.
#define cimg_verbosity 0

// Configure display framework.
//
// Define 'cimg_display' to: '0' to disable display capabilities.
//                           '1' to use the X-Window framework (X11).
//                           '2' to use the Microsoft GDI32 framework.
#define cimg_display 0
