//
// Created by utopia on 2025/4/23.
//

#ifndef ANIMATIONSTACKEDWIDGET_H
#define ANIMATIONSTACKEDWIDGET_H

#include <QStackedWidget>
#include <QPropertyAnimation>



class AnimationStackedWidget : public QStackedWidget {
Q_OBJECT
public:
    enum AnimationType{
        TopToBottom,    ///Animation from top to bottom
        BottomToTop,    ///Animation from bottom to top
        LeftToRight,    ///Animation from left to right
        RightToLeft     ///Animation from right to left
    };

public:
    explicit AnimationStackedWidget(QWidget *parent = nullptr);
    ~AnimationStackedWidget() override;

    static QString getClassName();
    void start(int index);
    void setIndex(int previous, int current);
    void setLength(int length, AnimationType type);
    void setDuration(int duration);
    int getDuration() const;

private slots:
    void valueChanged(const QVariant &value);
    void animationFinished();

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    void renderPreviousWidget(QPainter &painter, QTransform &transform);
    void renderCurrentWidget(QPainter &painter, QTransform &transform);

private:
    bool m_isAnimating;
    float m_currentValue;
    int m_currentIndex, m_previousIndex;
    AnimationType m_type;
    QPropertyAnimation *m_animation;
};


#endif //ANIMATIONSTACKEDWIDGET_H
