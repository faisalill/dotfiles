/* See LICENSE file for copyright and license details. */
/* Wallpaper Manager */
static const char *wallpaper[] = {
    "feh", "--bg-scale", "/home/kenny/Pictures/wallpapers/black.jpg", NULL};
/* appearance */
static const unsigned int borderpx = 1; /* border pixel of windows */
static const unsigned int snap = 32;    /* snap pixel */
static const int showbar = 1;           /* 0 means no bar */
static const int topbar = 1;            /* 0 means bottom bar */
static const char *fonts[] = {"JetBrainsMono Nerd Font:size=10:style=bold"};
static const char dmenufont[] = "JetBrainsMono Nerd Font:size=10:style=bold";
static const char col_gray1[] = "#222222";
static const char black[] = "#000000";
static const char white[] = "#FFFFFF";
static const char col_gray2[] = "#444444";
static const char col_gray3[] = "#bbbbbb";
static const char col_gray4[] = "#eeeeee";
static const char col_cyan[] = "#005577";
static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {white, black, white},
    [SchemeSel] = {white, black, white},
};

/* tagging */
static const char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    // {"Gimp", NULL, NULL, 0, 1, -1},
    // {"Firefox", NULL, NULL, 1 << 8, 0, -1},
    {NULL, NULL, NULL, 0, False, -1},
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    0; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[T]", tile}, /* first entry is default */
    {"[N]", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
    "dmenu_run", "-m",      dmenumon, "-fn",    dmenufont, "-nb",     col_gray1,
    "-nf",       col_gray3, "-sb",    col_cyan, "-sf",     col_gray4, NULL};
static const char *termcmd[] = {"st", NULL};

void viewadjacent(const Arg *arg);
void focusstackvertical(const Arg *arg);
void togglefullscreen(const Arg *arg);
void swapclientdirection(const Arg *arg);
// void setfullscreen(Client *c, int fullscreen);
static const Key keys[] = {
    /* modifier                     key        function        argument */
    {MODKEY, XK_space, spawn, {.v = dmenucmd}},
    {MODKEY | ShiftMask, XK_Return, spawn, {.v = termcmd}},
    {MODKEY, XK_Return, spawn, SHCMD("st")},
    {MODKEY, XK_b, togglebar, {0}},
    {Mod1Mask, XK_l, focusstack, {.i = +1}},
    {Mod1Mask, XK_h, focusstack, {.i = -1}},
    {Mod1Mask, XK_j, focusstackvertical, {.i = +1}},
    {Mod1Mask, XK_k, focusstackvertical, {.i = -1}},
    {MODKEY, XK_l, viewadjacent, {.i = +1}},
    {MODKEY, XK_h, viewadjacent, {.i = -1}},
    {MODKEY, XK_f, togglefullscreen, {0}},
    // {Mod1Mask, XK_o, incnmaster, {.i = +1}},
    // {Mod1Mask, XK_i, incnmaster, {.i = -1}},
    {Mod1Mask, XK_i, setmfact, {.f = -0.05}},
    {Mod1Mask, XK_o, setmfact, {.f = +0.05}},
    {MODKEY, XK_Tab, view, {0}},
    // {MODKEY | ShiftMask, XK_c, killclient, {0}},
    {MODKEY, XK_k, killclient, {0}},
    {MODKEY | Mod1Mask, XK_k, swapclientdirection, {.i = 0}}, // Swap up
    {MODKEY | Mod1Mask, XK_j, swapclientdirection, {.i = 1}}, // Swap down
    {MODKEY | Mod1Mask, XK_h, swapclientdirection, {.i = 2}}, // Swap left
    {MODKEY | Mod1Mask, XK_l, swapclientdirection, {.i = 3}},
    {MODKEY, XK_F2, spawn, SHCMD("amixer set Master 5%-")}, // Decrease volume
    {MODKEY, XK_F3, spawn, SHCMD("amixer set Master 5%+")}, // Increase volume
    {MODKEY, XK_F1, spawn, SHCMD("amixer set Master toggle")},
    {MODKEY, XK_F7, spawn, SHCMD("brightnessctl s 10%-")},
    {MODKEY, XK_F8, spawn, SHCMD("brightnessctl s 10%+")},
    // {MODKEY, XK_t, setlayout, {.v =
    // &layouts[0]}}, {MODKEY, XK_f,
    // setlayout, {.v = &layouts[1]}},
    // {MODKEY, XK_m, setlayout, {.v =
    // &layouts[2]}}, {MODKEY, XK_f,
    // setlayout, {0}}, {MODKEY, XK_g,
    // togglefloating, {0}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8){MODKEY | ShiftMask, XK_q, quit, {0}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function argument
     */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};

void viewadjacent(const Arg *arg) {
  int i = selmon->tagset[selmon->seltags];
  if (arg->i > 0) { // next tag
    i = (i == (1 << (LENGTH(tags) - 1))) ? 1 : i << 1;
  } else { // previous tag
    i = (i == 1) ? (1 << (LENGTH(tags) - 1)) : i >> 1;
  }
  view(&(Arg){.ui = i});
}

void focusstackvertical(const Arg *arg) {
  Client *c = NULL, *i;

  if (!selmon->sel)
    return;

  if (arg->i > 0) {
    /* focus next client */
    for (c = selmon->sel->next; c && !ISVISIBLE(c); c = c->next)
      ;
    if (!c)
      for (c = selmon->clients; c && !ISVISIBLE(c); c = c->next)
        ;
  } else {
    /* focus previous client */
    for (i = selmon->clients; i != selmon->sel; i = i->next)
      if (ISVISIBLE(i))
        c = i;
    if (!c)
      for (; i; i = i->next)
        if (ISVISIBLE(i))
          c = i;
  }

  if (c) {
    focus(c);
    restack(selmon);
  }
}

void togglefullscreen(const Arg *arg) {
  if (!selmon->sel)
    return;
  setfullscreen(selmon->sel, !selmon->sel->isfullscreen);
}

// void setfullscreen(Client *c, int fullscreen) {
//   if (fullscreen && !c->isfullscreen) {
//     XChangeProperty(dpy, c->win, netatom[NetWMState], XA_ATOM, 32,
//                     PropModeReplace, (unsigned char
//                     *)&netatom[NetWMFullscreen], 1);
//     c->isfullscreen = 1;
//     c->oldstate = c->isfloating;
//     c->oldbw = c->bw;
//     c->bw = 0;
//     c->isfloating = 1;
//     resizeclient(c, selmon->mx, selmon->my, selmon->mw, selmon->mh);
//     XRaiseWindow(dpy, c->win);
//   } else if (!fullscreen && c->isfullscreen) {
//     XChangeProperty(dpy, c->win, netatom[NetWMState], XA_ATOM, 32,
//                     PropModeReplace, (unsigned char *)0, 0);
//     c->isfullscreen = 0;
//     c->isfloating = c->oldstate;
//     c->bw = c->oldbw;
//     resize(c, c->x, c->y, c->w, c->h, 0);
//   }
// }

void swapclientdirection(const Arg *arg) {
  if (!selmon->sel || !selmon->clients)
    return;

  Client *c = selmon->sel;
  Client *best = NULL;
  int mindistance = INT_MAX;
  int cx = c->x + c->w / 2;
  int cy = c->y + c->h / 2;

  for (Client *tmp = selmon->clients; tmp; tmp = tmp->next) {
    if (tmp == c || !ISVISIBLE(tmp))
      continue;

    int tx = tmp->x + tmp->w / 2;
    int ty = tmp->y + tmp->h / 2;
    int distance = abs(cx - tx) + abs(cy - ty);

    switch (arg->i) {
    case 0: // Swap up
      if (ty < cy && distance < mindistance) {
        best = tmp;
        mindistance = distance;
      }
      break;
    case 1: // Swap down
      if (ty > cy && distance < mindistance) {
        best = tmp;
        mindistance = distance;
      }
      break;
    case 2: // Swap left
      if (tx < cx && distance < mindistance) {
        best = tmp;
        mindistance = distance;
      }
      break;
    case 3: // Swap right
      if (tx > cx && distance < mindistance) {
        best = tmp;
        mindistance = distance;
      }
      break;
    }
  }

  if (!best)
    return;

  // Swap positions in the client list
  Client *prev_c = NULL, *prev_best = NULL, *tmp;

  for (tmp = selmon->clients; tmp && tmp != c; tmp = tmp->next)
    prev_c = tmp;
  for (tmp = selmon->clients; tmp && tmp != best; tmp = tmp->next)
    prev_best = tmp;

  if (prev_c)
    prev_c->next = best;
  if (prev_best)
    prev_best->next = c;

  tmp = c->next;
  c->next = best->next;
  best->next = tmp;

  if (selmon->clients == c)
    selmon->clients = best;
  else if (selmon->clients == best)
    selmon->clients = c;

  focus(c);
  arrange(selmon);
}
