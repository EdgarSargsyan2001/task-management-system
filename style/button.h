#ifndef BUTTON_H
#define BUTTON_H

const QString button_style = "QPushButton{ "
                             "background-color: "
                             "qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
                             "stop:0 rgba(194, 164, 122, 255), stop:1 rgba(0, 40, 85, 255));"
                             ""
                             "color:rgb(255,255,255);"
                             "border-radius:5px; "
                             "padding-bottom:4px;"
                             "font-size:21px;"

                             "}";

const QString button_style_hover = "QPushButton:hover{"
                                   "background-color: "
                                   "qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
                                   "stop:0 rgba(255, 255, 255, 255), "
                                   "stop:1 rgba(0, 40, 85, 255));"
                                   "}";

const QString button_style_pressed = "QPushButton:pressed{"
                                     "margin:1px;"
                                     "}";

#endif // BUTTON_H
