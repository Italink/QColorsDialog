#include "AeroDialog.h"
#include "QNeumorphism/QNeumorphism.h"
#include <QPainter>
#include <QDebug>
#include <QApplication>

typedef enum _WINDOWCOMPOSITIONATTRIB{
    WCA_UNDEFINED = 0,
    WCA_NCRENDERING_ENABLED = 1,
    WCA_NCRENDERING_POLICY = 2,
    WCA_TRANSITIONS_FORCEDISABLED = 3,
    WCA_ALLOW_NCPAINT = 4,
    WCA_CAPTION_BUTTON_BOUNDS = 5,
    WCA_NONCLIENT_RTL_LAYOUT = 6,
    WCA_FORCE_ICONIC_REPRESENTATION = 7,
    WCA_EXTENDED_FRAME_BOUNDS = 8,
    WCA_HAS_ICONIC_BITMAP = 9,
    WCA_THEME_ATTRIBUTES = 10,
    WCA_NCRENDERING_EXILED = 11,
    WCA_NCADORNMENTINFO = 12,
    WCA_EXCLUDED_FROM_LIVEPREVIEW = 13,
    WCA_VIDEO_OVERLAY_ACTIVE = 14,
    WCA_FORCE_ACTIVEWINDOW_APPEARANCE = 15,
    WCA_DISALLOW_PEEK = 16,
    WCA_CLOAK = 17,
    WCA_CLOAKED = 18,
    WCA_ACCENT_POLICY = 19,
    WCA_FREEZE_REPRESENTATION = 20,
    WCA_EVER_UNCLOAKED = 21,
    WCA_VISUAL_OWNER = 22,
    WCA_LAST = 23
} WINDOWCOMPOSITIONATTRIB;
typedef struct _WINDOWCOMPOSITIONATTRIBDATA{
    WINDOWCOMPOSITIONATTRIB Attrib;
    PVOID pvData;
    SIZE_T cbData;
} WINDOWCOMPOSITIONATTRIBDATA;
typedef enum _ACCENT_STATE{
    ACCENT_DISABLED = 0,
    ACCENT_ENABLE_GRADIENT = 1,
    ACCENT_ENABLE_TRANSPARENTGRADIENT = 2,
    ACCENT_ENABLE_BLURBEHIND = 3,
    ACCENT_INVALID_STATE = 4
} ACCENT_STATE;
typedef struct _ACCENT_POLICY
{
    ACCENT_STATE AccentState;
    DWORD AccentFlags;
    DWORD GradientColor;
    DWORD AnimationId;
} ACCENT_POLICY;
WINUSERAPI
BOOL
WINAPI
GetWindowCompositionAttribute(
    _In_ HWND hWnd,
    _Inout_ WINDOWCOMPOSITIONATTRIBDATA* pAttrData);
typedef BOOL(WINAPI*pfnGetWindowCompositionAttribute)(HWND, WINDOWCOMPOSITIONATTRIBDATA*);
WINUSERAPI
BOOL
WINAPI
SetWindowCompositionAttribute(
    _In_ HWND hWnd,
    _Inout_ WINDOWCOMPOSITIONATTRIBDATA* pAttrData);
typedef BOOL(WINAPI*pfnSetWindowCompositionAttribute)(HWND, WINDOWCOMPOSITIONATTRIBDATA*);


AeroDialog::AeroDialog(const QString &title, QWidget *parent)
    : QDialog(parent)
    , vLayout(this)
    , boundaryWidth(5)
{
    QLabel *headerBar=new QLabel(title);
    headerBar->setMargin(4);
    QFont font=qApp->font();
    font.setFamily("微软雅黑");
    font.setPixelSize(15);
    headerBar->setFont(font);
    CloseButton* btClose=new CloseButton();
    MaximizeButton* btMaximizeSize=new  MaximizeButton();
    QHBoxLayout *h=new QHBoxLayout();

    h->addWidget(headerBar);
    h->addWidget(btMaximizeSize);
    h->addWidget(btClose);

    setMinimumSize(100,100);
    vLayout.addLayout(h);
    vLayout.setAlignment(Qt::AlignTop);
    vLayout.setMargin(0);
    vLayout.setSpacing(0);
    setWindowFlags(Qt::FramelessWindowHint|Qt::CustomizeWindowHint|Qt::Window|Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);

    HWND hWnd = HWND(winId());
    HMODULE hUser = GetModuleHandle(L"user32.dll");
    if (hUser)
    {
        pfnSetWindowCompositionAttribute setWindowCompositionAttribute = (pfnSetWindowCompositionAttribute)GetProcAddress(hUser, "SetWindowCompositionAttribute");
        if (setWindowCompositionAttribute)
        {
            ACCENT_POLICY accent = { ACCENT_ENABLE_BLURBEHIND, 0, 0, 0 };
            WINDOWCOMPOSITIONATTRIBDATA data;
            data.Attrib = WCA_ACCENT_POLICY;
            data.pvData = &accent;
             data.cbData = sizeof(accent);
            setWindowCompositionAttribute(hWnd, &data);
        }
    }
    connect(btClose,&CloseButton::pressed,this,&QWidget::close);
    connect( btMaximizeSize,&MaximizeButton::pressed,this,[this](){
        if(isFullScreen()){
            showNormal();
        }
        else{
            showFullScreen();
        }

    });
}


bool AeroDialog::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    MSG* msg = (MSG*)message;
    switch(msg->message)
        {
        case WM_NCHITTEST:

            int xPos = QCursor::pos().x() - this->geometry().x();
            int yPos = QCursor::pos().y() - this->geometry().y();
            if(xPos < boundaryWidth && yPos<boundaryWidth)
                *result = HTTOPLEFT;
           else if(xPos>=width()-boundaryWidth&&yPos<boundaryWidth)
                *result = HTTOPRIGHT;
            else if(xPos<boundaryWidth&&yPos>=height()-boundaryWidth)
                *result = HTBOTTOMLEFT;
            else if(xPos>=width()-boundaryWidth&&yPos>=height()-boundaryWidth)
                *result = HTBOTTOMRIGHT;
            else if(xPos < boundaryWidth)                                     //左边
                *result =  HTLEFT;
            else if(xPos>=width()-boundaryWidth)                              //右边
                *result = HTRIGHT;
            else if(yPos<boundaryWidth)                                       //上边
                *result = HTTOP;
            else if(yPos>=height()-boundaryWidth)                             //下边
                *result = HTBOTTOM;
            else              //其他部分不做处理，返回false，留给其他事件处理器处理
               return false;
            return true;
        }
        return false;         //此处返回false，留给其他事件处理器处理
}

void AeroDialog::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton&&!isFullScreen())
        clickPos=e->pos();
}
void AeroDialog::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons()&Qt::LeftButton&&!clickPos.isNull()&&!isFullScreen()&&e->y())
        move(e->pos()+pos()-clickPos);
}

void AeroDialog::mouseReleaseEvent(QMouseEvent *)
{
    clickPos={0,0};
}

void AeroDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(QColor(0,0,0,80));
    painter.setBrush(QColor(255,255,255,100));
    painter.drawRect(rect().adjusted(1,1,-1,-1));
}

void AeroDialog::showEvent(QShowEvent *)
{
    clickPos={0,0};
}

CloseButton::CloseButton(QWidget *parent)
    :QWidget(parent)
    ,enter(false)
{
    setFixedSize(30,30);
    setGraphicsEffect(new QNeumorphism);
}

CloseButton::~CloseButton()
{
}

void CloseButton::mousePressEvent(QMouseEvent*)
{
    emit pressed();
}

void CloseButton::enterEvent(QEvent *)
{
    enter=true;
    update();
}

void CloseButton::leaveEvent(QEvent *)
{
    enter=false;
    update();
}

void CloseButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidth(3);
    if(enter){
        painter.fillRect(rect(),QColor(255,0,0,100));
        pen.setColor(Qt::white);
    }
    else
        pen.setColor(QColor(255,0,0));
    QRect re=rect().adjusted(8,8,-8,-8);
    painter.setPen(pen);
    painter.drawLine(re.bottomLeft(),re.topRight());
    painter.drawLine(re.topLeft(),re.bottomRight());
}


void MaximizeButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    painter.setRenderHint(QPainter::Antialiasing);
    pen.setWidth(3);
    if(enter){
        painter.fillRect(rect(),QColor(0,90,170,100));
        pen.setColor(Qt::white);
    }
    else
        pen.setColor(QColor(0,90,170));
    QRect re=rect().adjusted(8,8,-8,-8);
    painter.setPen(pen);
    painter.drawRect(re);
}
