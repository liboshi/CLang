/*

   Copyright (c) 1988  X Consortium

   Permission is hereby granted, free of charge, to any person obtaining
   a copy of this software and associated documentation files (the
   "Software"), to deal in the Software without restriction, including
   without limitation the rights to use, copy, modify, merge, publish,
   distribute, sublicense, and/or sell copies of the Software, and to
   permit persons to whom the Software is furnished to do so, subject to
   the following conditions:

   The above copyright notice and this permission notice shall be included
   in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE X CONSORTIUM BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.

   Except as contained in this notice, the name of the X Consortium shall
   not be used in advertising or otherwise to promote the sale, use or
   other dealings in this Software without prior written authorization
   from the X Consortium.

*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <X11/Xlocale.h>
#include <X11/Xos.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/Xproto.h>
#include <X11/extensions/Xrandr.h>

#define INNER_WINDOW_WIDTH 200
#define INNER_WINDOW_HEIGHT 100
#define INNER_WINDOW_BORDER 4
#define INNER_WINDOW_X 0
#define INNER_WINDOW_Y 0
#define OUTER_WINDOW_MIN_WIDTH (INNER_WINDOW_WIDTH + \
                2 * (INNER_WINDOW_BORDER + INNER_WINDOW_X))
#define OUTER_WINDOW_MIN_HEIGHT (INNER_WINDOW_HEIGHT + \
                2 * (INNER_WINDOW_BORDER + INNER_WINDOW_Y))
#define OUTER_WINDOW_DEF_WIDTH (OUTER_WINDOW_MIN_WIDTH + 100)
#define OUTER_WINDOW_DEF_HEIGHT (OUTER_WINDOW_MIN_HEIGHT + 100)
#define OUTER_WINDOW_DEF_X 100
#define OUTER_WINDOW_DEF_Y 100

#define DEBUG 0

int RELEASE = 0;
char *output_log = "/tmp/inputResult.log";

typedef unsigned long Pixel;

const char *Yes = "YES";
const char *No = "NO";
const char *Unknown = "unknown";

const char *ProgramName;
Display *dpy;
int screen;

XIC xic = NULL;

Atom wm_delete_window;
Atom wm_protocols;

Bool have_rr;
int rr_event_base, rr_error_base;

static void usage (void) _X_NORETURN;

static void
dump (char *str, int len)
{
        printf("(");
        len--;
        while (len-- > 0)
                printf("%02x ", (unsigned char) *str++);
        printf("%02x)", (unsigned char) *str++);
}

static void
do_KeyPress (XEvent *eventp)
{
        XKeyEvent *e = (XKeyEvent *) eventp;
        KeySym ks;
        KeyCode kc = 0;
        Bool kc_set = False;
        const char *ksname;
        int nbytes, nmbbytes = 0;
        char str[256+1];
        static char *buf = NULL;
        static int bsize = 8;
        Status status;
        FILE *fd_log;

        if (buf == NULL)
                buf = malloc (bsize);

        nbytes = XLookupString (e, str, 256, &ks, NULL);

        /* not supposed to call XmbLookupString on a key release event */
        if (e->type == KeyPress && xic) {
                do {
                        nmbbytes = XmbLookupString (xic, e, buf, bsize - 1, &ks, &status);
                        buf[nmbbytes] = '\0';

                        if (status == XBufferOverflow) {
                                bsize = nmbbytes + 1;
                                buf = realloc (buf, bsize);
                        }
                } while (status == XBufferOverflow);
        }

        if (ks == NoSymbol)
                ksname = "NoSymbol";
        else {
                if (!(ksname = XKeysymToString (ks)))
                        ksname = "(no name)";
                kc = XKeysymToKeycode(dpy, ks);
                kc_set = True;
        }


        if (RELEASE == 1) {
                fd_log = fopen(output_log, "a");
                fprintf(fd_log, "%s ", ksname);
                fclose(fd_log);
        }
        RELEASE = 0;
        printf ("%s ", ksname);
        if (kc_set && e->keycode != kc)
                ;
        if (nbytes < 0) nbytes = 0;
        if (nbytes > 256) nbytes = 256;
        str[nbytes] = '\0';
        if (nbytes > 0) {
                ;
        } else {
                ;
        }

        /* not supposed to call XmbLookupString on a key release event */
        if (e->type == KeyPress && xic) {
                if (nmbbytes > 0) {
                        ;
                } else {
                        ;
                }
        }

}

static void
do_KeyRelease (XEvent *eventp)
{
        RELEASE = 1;
        do_KeyPress (eventp);		/* since it has the same info */
}

static void
do_ButtonPress (XEvent *eventp)
{
        XButtonEvent *e = (XButtonEvent *) eventp;

        printf ("    state 0x%x, button %u, same_screen %s\n",
                        e->state, e->button, e->same_screen ? Yes : No);
}

static void
do_ButtonRelease (XEvent *eventp)
{
        do_ButtonPress (eventp);		/* since it has the same info */
}

static void
do_FocusIn (XEvent *eventp)
{
        XFocusChangeEvent *e = (XFocusChangeEvent *) eventp;
        const char *mode, *detail;
        char dmode[10], ddetail[10];

        switch (e->mode) {
                case NotifyNormal:  mode = "NotifyNormal"; break;
                case NotifyGrab:  mode = "NotifyGrab"; break;
                case NotifyUngrab:  mode = "NotifyUngrab"; break;
                case NotifyWhileGrabbed:  mode = "NotifyWhileGrabbed"; break;
                default:  mode = dmode, sprintf (dmode, "%u", e->mode); break;
        }

        switch (e->detail) {
                case NotifyAncestor:  detail = "NotifyAncestor"; break;
                case NotifyVirtual:  detail = "NotifyVirtual"; break;
                case NotifyInferior:  detail = "NotifyInferior"; break;
                case NotifyNonlinear:  detail = "NotifyNonlinear"; break;
                case NotifyNonlinearVirtual:  detail = "NotifyNonlinearVirtual"; break;
                case NotifyPointer:  detail = "NotifyPointer"; break;
                case NotifyPointerRoot:  detail = "NotifyPointerRoot"; break;
                case NotifyDetailNone:  detail = "NotifyDetailNone"; break;
                default:  detail = ddetail; sprintf (ddetail, "%u", e->detail); break;
        }
}

static void
do_FocusOut (XEvent *eventp)
{
        do_FocusIn (eventp);		/* since it has same information */
}

static void
set_sizehints (XSizeHints *hintp, int min_width, int min_height,
                int defwidth, int defheight, int defx, int defy,
                char *geom)
{
        int geom_result;

        /* set the size hints, algorithm from xlib xbiff */

        hintp->width = hintp->min_width = min_width;
        hintp->height = hintp->min_height = min_height;
        hintp->flags = PMinSize;
        hintp->x = hintp->y = 0;
        geom_result = NoValue;
        if (geom != NULL) {
                geom_result = XParseGeometry (geom, &hintp->x, &hintp->y,
                                (unsigned int *)&hintp->width,
                                (unsigned int *)&hintp->height);
                if ((geom_result & WidthValue) && (geom_result & HeightValue)) {
#ifndef max
#define max(a,b) ((a) > (b) ? (a) : (b))
#endif
                        hintp->width = max (hintp->width, hintp->min_width);
                        hintp->height = max (hintp->height, hintp->min_height);
                        hintp->flags |= USSize;
                }
                if ((geom_result & XValue) && (geom_result & YValue)) {
                        hintp->flags += USPosition;
                }
        }
        if (!(hintp->flags & USSize)) {
                hintp->width = defwidth;
                hintp->height = defheight;
                hintp->flags |= PSize;
        }
        /*
           if (!(hintp->flags & USPosition)) {
           hintp->x = defx;
           hintp->y = defy;
           hintp->flags |= PPosition;
           }
           */
        if (geom_result & XNegative) {
                hintp->x = DisplayWidth (dpy, DefaultScreen (dpy)) + hintp->x -
                        hintp->width;
        }
        if (geom_result & YNegative) {
                hintp->y = DisplayHeight (dpy, DefaultScreen (dpy)) + hintp->y -
                        hintp->height;
        }
}

static void
usage (void)
{
        static const char *msg[] = {
                "    -display displayname                X server to contact",
                "    -geometry geom                      size and location of window",
                "    -bw pixels                          border width in pixels",
                "    -bs {NotUseful,WhenMapped,Always}   backingstore attribute",
                "    -id windowid                        use existing window",
                "    -root                               use root window",
                "    -s                                  set save-unders attribute",
                "    -name string                        window name",
                "    -rv                                 reverse video",
                "",
                NULL};
        const char **cpp;

        fprintf (stderr, "usage:  %s [-options ...]\n", ProgramName);
        fprintf (stderr, "where options include:\n");

        for (cpp = msg; *cpp; cpp++)
                fprintf (stderr, "%s\n", *cpp);

        exit (1);
}

static int
parse_backing_store (char *s)
{
        int len = strlen (s);
        char *cp;

        for (cp = s; *cp; cp++) {
                if (isascii (*cp) && isupper (*cp))
                        *cp = tolower (*cp);
        }

        if (strncmp (s, "notuseful", len) == 0) return (NotUseful);
        if (strncmp (s, "whenmapped", len) == 0) return (WhenMapped);
        if (strncmp (s, "always", len) == 0) return (Always);

        usage ();
}

keep_window_always_top(Display *dpy, Window w)
{
        Atom stateAbove;
        if (w) {
                stateAbove = XInternAtom(dpy, "_NET_WM_STATE_ABOVE", False);
                XChangeProperty(dpy, w,
                                XInternAtom(dpy, "_NET_WM_STATE", False),
                                XA_ATOM, 32,
                                PropModeReplace, (unsigned char *) &stateAbove,
                                1);
        }
        return ;
}

int
main (int argc, char **argv)
{
        char *displayname = NULL;
        char *geom = NULL;
        int i;
        XSizeHints hints;
        int borderwidth = 2;
        Window w;
        XSetWindowAttributes attr;
        XWindowAttributes wattr;
        unsigned long mask = 0L;
        int done;
        const char *name = "InputMonitor";
        Bool reverse = False;
        Bool use_root = False;
        unsigned long back, fore;
        XIM xim;
        XIMStyles *xim_styles;
        XIMStyle xim_style = 0;
        char *modifiers;
        char *imvalret;

        ProgramName = argv[0];

        if (setlocale(LC_ALL,"") == NULL) {
                fprintf(stderr, "%s: warning: could not set default locale\n",
                                ProgramName);
        }

        w = 0;
        for (i = 1; i < argc; i++) {
                char *arg = argv[i];
                if (i == 1) {
                        output_log = argv[i];
                        continue;
                }

                if (arg[0] == '-') {
                        switch (arg[1]) {
                                case 'd':			/* -display host:dpy */
                                        if (++i >= argc) usage ();
                                        displayname = argv[i];
                                        continue;
                                case 'g':			/* -geometry geom */
                                        if (++i >= argc) usage ();
                                        geom = argv[i];
                                        continue;
                                case 'b':
                                        switch (arg[2]) {
                                                case 'w':		/* -bw pixels */
                                                        if (++i >= argc) usage ();
                                                        borderwidth = atoi (argv[i]);
                                                        continue;
                                                case 's':		/* -bs type */
                                                        if (++i >= argc) usage ();
                                                        attr.backing_store = parse_backing_store (argv[i]);
                                                        mask |= CWBackingStore;
                                                        continue;
                                                default:
                                                        usage ();
                                        }
                                case 'i':			/* -id */
                                        if (++i >= argc) usage ();
                                        sscanf(argv[i], "0x%lx", &w);
                                        if (!w)
                                                sscanf(argv[i], "%lu", &w);
                                        if (!w)
                                                usage ();
                                        continue;
                                case 'n':			/* -name */
                                        if (++i >= argc) usage ();
                                        name = argv[i];
                                        continue;
                                case 'r':
                                        switch (arg[2]) {
                                                case 'o':		/* -root */
                                                        use_root = True;
                                                        continue;
                                                case 'v':		/* -rv */
                                                        reverse = True;
                                                        continue;
                                                default:
                                                        usage ();
                                        }
                                        continue;
                                case 's':			/* -s */
                                        attr.save_under = True;
                                        mask |= CWSaveUnder;
                                        continue;
                                default:
                                        usage ();
                        }				/* end switch on - */
                } else
                        usage ();
        }					/* end for over argc */
        /* Clear the contents in input monitor log */
        fclose(fopen(output_log, "w"));

        dpy = XOpenDisplay (displayname);
        if (!dpy) {
                fprintf (stderr, "%s:  unable to open display '%s'\n",
                                ProgramName, XDisplayName (displayname));
                exit (1);
        }

        /* we're testing the default input method */
        modifiers = XSetLocaleModifiers ("@im=none");
        if (modifiers == NULL) {
                fprintf (stderr, "%s:  XSetLocaleModifiers failed\n", ProgramName);
        }

        xim = XOpenIM (dpy, NULL, NULL, NULL);
        if (xim == NULL) {
                fprintf (stderr, "%s:  XOpenIM failed\n", ProgramName);
        }

        if (xim) {
                imvalret = XGetIMValues (xim, XNQueryInputStyle, &xim_styles, NULL);
                if (imvalret != NULL || xim_styles == NULL) {
                        fprintf (stderr, "%s:  input method doesn't support any styles\n", ProgramName);
                }

                if (xim_styles) {
                        xim_style = 0;
                        for (i = 0;  i < xim_styles->count_styles;  i++) {
                                if (xim_styles->supported_styles[i] ==
                                                (XIMPreeditNothing | XIMStatusNothing)) {
                                        xim_style = xim_styles->supported_styles[i];
                                        break;
                                }
                        }

                        if (xim_style == 0) {
                                fprintf (stderr, "%s: input method doesn't support the style we support\n",
                                                ProgramName);
                        }
                        XFree (xim_styles);
                }
        }

        screen = DefaultScreen (dpy);

        /* select for all events */
        attr.event_mask = KeyPressMask | KeyReleaseMask | ButtonPressMask |
                ButtonReleaseMask | EnterWindowMask |
                LeaveWindowMask | PointerMotionMask |
                Button1MotionMask |
                Button2MotionMask | Button3MotionMask |
                Button4MotionMask | Button5MotionMask |
                ButtonMotionMask | KeymapStateMask |
                ExposureMask | VisibilityChangeMask |
                StructureNotifyMask | /* ResizeRedirectMask | */
                SubstructureNotifyMask | SubstructureRedirectMask |
                FocusChangeMask | PropertyChangeMask |
                ColormapChangeMask | OwnerGrabButtonMask;

        if (use_root)
                w = RootWindow(dpy, screen);

        if (w) {
                XGetWindowAttributes(dpy, w, &wattr);
                if (wattr.all_event_masks & ButtonPressMask)
                        attr.event_mask &= ~ButtonPressMask;
                attr.event_mask &= ~SubstructureRedirectMask;
                XSelectInput(dpy, w, attr.event_mask);
        } else {
                set_sizehints (&hints, OUTER_WINDOW_MIN_WIDTH, OUTER_WINDOW_MIN_HEIGHT,
                                OUTER_WINDOW_DEF_WIDTH, OUTER_WINDOW_DEF_HEIGHT,
                                OUTER_WINDOW_DEF_X, OUTER_WINDOW_DEF_Y, geom);

                if (reverse) {
                        back = BlackPixel(dpy,screen);
                        fore = WhitePixel(dpy,screen);
                } else {
                        back = WhitePixel(dpy,screen);
                        fore = BlackPixel(dpy,screen);
                }

                attr.background_pixel = back;
                attr.border_pixel = fore;
                mask |= (CWBackPixel | CWBorderPixel | CWEventMask);

                w = XCreateWindow (dpy, RootWindow (dpy, screen), hints.x, hints.y,
                                hints.width, hints.height, borderwidth, 0,
                                InputOutput, (Visual *)CopyFromParent,
                                mask, &attr);

                XSetStandardProperties (dpy, w, name, NULL, (Pixmap) 0,
                                argv, argc, &hints);

                keep_window_always_top(dpy, w);
                wm_protocols = XInternAtom(dpy, "WM_PROTOCOLS", False);
                wm_delete_window = XInternAtom(dpy, "WM_DELETE_WINDOW", False);
                XSetWMProtocols(dpy, w, &wm_delete_window, 1);

                XMapWindow (dpy, w);
        }

        if (xim && xim_style) {
                xic = XCreateIC (xim,
                                XNInputStyle, xim_style,
                                XNClientWindow, w,
                                XNFocusWindow, w,
                                NULL);

                if (xic == NULL) {
                        fprintf (stderr, "XCreateIC failed\n");
                }
        }

        have_rr = XRRQueryExtension (dpy, &rr_event_base, &rr_error_base);
        if (have_rr) {
                int rr_major, rr_minor;

                if (XRRQueryVersion (dpy, &rr_major, &rr_minor)) {
                        int rr_mask = RRScreenChangeNotifyMask;

                        if (rr_major > 1
                                        || (rr_major == 1 && rr_minor >= 2))
                                rr_mask |= RRCrtcChangeNotifyMask | RROutputChangeNotifyMask |
                                        RROutputPropertyNotifyMask;
                        XRRSelectInput (dpy, w, rr_mask);
                }
        }

        for (done = 0; !done; ) {
                XEvent event;

                XNextEvent (dpy, &event);

                switch (event.type) {
                        case KeyPress:
                                do_KeyPress (&event);
                                break;
                        case KeyRelease:
                                do_KeyRelease (&event);
                                break;
                        case ButtonPress:
                                do_ButtonPress (&event);
                                break;
                        case ButtonRelease:
                                do_ButtonRelease (&event);
                                break;
                        case FocusIn:
                                do_FocusIn (&event);
                                break;
                        case FocusOut:
                                do_FocusOut (&event);
                                break;
                        default:
                                break;
                }
                fflush(stdout);
        }

        XCloseDisplay (dpy);
        return 0;
}
