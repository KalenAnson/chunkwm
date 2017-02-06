#ifndef AXLIB_WINDOW_H
#define AXLIB_WINDOW_H

#include <Carbon/Carbon.h>

enum macos_window_flags
{
    Window_Movable = (1 << 0),
    Window_Resizable = (1 << 1),
    Window_Minimized = (1 << 2),
    Window_Floating = (1 << 3),
};

struct macos_application;
struct macos_window
{
    AXUIElementRef Ref;
    CFTypeRef Mainrole;
    CFTypeRef Subrole;

    // NOTE(koekeishiya): Store Owner->PID instead ?
    macos_application *Owner;
    uint32_t Id;
    char *Name;

    CGPoint Position;
    CGSize Size;

    uint32_t Flags;
};

macos_window *AXLibConstructWindow(macos_application *Application, AXUIElementRef WindowRef);
macos_window *AXLibCopyWindow(macos_window *Window);
void AXLibDestroyWindow(macos_window *Window);

bool AXLibIsWindowStandard(macos_window *Window);
bool AXLibWindowHasRole(macos_window *Window, CFTypeRef Role);

macos_window **AXLibWindowListForApplication(macos_application *Application);

/* NOTE(koekeishiya): This is not a thing for now.
 * bool AXLibIsWindowCustom(macos_window *Window);
 * bool AXLibWindowHasCustomRole(macos_window *Window, CFTypeRef Role);
 * */

inline void
AXLibAddFlags(macos_window *Window, uint32_t Flag)
{
    Window->Flags |= Flag;
}

inline void
AXLibClearFlags(macos_window *Window, uint32_t Flag)
{
    Window->Flags &= ~Flag;
}

inline bool
AXLibHasFlags(macos_window *Window, uint32_t Flag)
{
    bool Result = ((Window->Flags & Flag) != 0);
    return Result;
}

#endif