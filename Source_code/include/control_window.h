/* 
================================================================================
Filename: control_window.h
Description: Declaration of the ControlWindow class methods.
================================================================================
*/

#ifndef CONTROL_WINDOW_H_
#define CONTROL_WINDOW_H_

// Standard includes:
#include <QWidget>

// Program includes:
#include <drawing_window.h>
#include "../build/debug/ui/ui_ControlWindow.h"

class DrawingWindow;

class ControlWindow : public QWidget
{
    // Class for the ControlWindow
    Q_OBJECT

public:
    // Constructor of the class
    ControlWindow(QWidget *parent = nullptr); 

    // Pointer to the DrowingWindow class
    DrawingWindow *drawing_window;

private slots:
    // Slot for change value signal from spbMaxMajorPoints
    void on_spbMinMajorPoints_valueChanged(int min_value);

    // Slot for change value signal from spbMinMajorPoints
    void on_spbMaxMajorPoints_valueChanged(int max_value);

    // Slot for change value signal from spbMaxSmoothPoints
    void on_spbMinSmoothPoints_valueChanged(int min_value);

    // Slot for change value signal from spbMinSmoothPoints
    void on_spbMaxSmoothPoints_valueChanged(int max_value);

    // Slot for change value signal from dspbMaxRoundQuality
    void on_dspbMinRoundQuality_valueChanged(double min_value);

    // Slot for change value signal from dspbMinRoundQuality
    void on_dspbMaxRoundQuality_valueChanged(double max_value);

    // Slot for the click signal from btnGeneratePolygon
    void on_btnGeneratePolygon_clicked();

protected:
    // Method to for handling the window close procedure
    void closeEvent(QCloseEvent *event) override;

private:
    // Form of the window
    Ui::ControlWindow ui;
};

#endif // CONTROL_WINDOW_H_
