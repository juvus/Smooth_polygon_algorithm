/* 
================================================================================
Filename: control_window.cpp
Description: Definition of the ControlWindow class methods.
================================================================================
*/

// Standard includes:
#include <QWidget>

// Program includes:
#include <control_window.h>
#include <constants.h>

ControlWindow::ControlWindow(QWidget *parent) : QWidget(parent)
{
    // Constructor of the ControlWindow class
    using namespace Constants;
    
    ui.setupUi(this);
    
    // Make the size of the window fixed
    u32 width = this->width();
    u32 height = this->height();
    this->setFixedSize(width, height);

    // Set widgets parameters and default values
    ui.spbMinMajorPoints->setRange(MIN_NUM_MAJOR_POINTS, MAX_NUM_MAJOR_POINTS);
    ui.spbMinMajorPoints->setValue(3);
    
    ui.spbMaxMajorPoints->setRange(MIN_NUM_MAJOR_POINTS, MAX_NUM_MAJOR_POINTS);
    ui.spbMaxMajorPoints->setValue(10);

    ui.spbMinSmoothPoints->setRange(MIN_NUM_SMOOTH_POINTS, MAX_NUM_SMOOTH_POINTS);
    ui.spbMinSmoothPoints->setValue(3);

    ui.spbMaxSmoothPoints->setRange(MIN_NUM_SMOOTH_POINTS, MAX_NUM_SMOOTH_POINTS);
    ui.spbMaxSmoothPoints->setValue(5);

    ui.dspbMinRoundQuality->setRange(MIN_ROUND_QUALITY, MAX_ROUND_QUALITY);
    ui.dspbMinRoundQuality->setValue(0.05);

    ui.dspbMaxRoundQuality->setRange(MIN_ROUND_QUALITY, MAX_ROUND_QUALITY);
    ui.dspbMaxRoundQuality->setValue(0.45);
}

void 
ControlWindow::on_spbMinMajorPoints_valueChanged(int min_value)
{
    // Slot for change value signal from spbMaxMajorPoints
    int max_value = ui.spbMaxMajorPoints->value();

    if (min_value > max_value)
        ui.spbMaxMajorPoints->setValue(min_value);
}

void
ControlWindow:: on_spbMaxMajorPoints_valueChanged(int max_value)
{
    // Slot for change value signal from spbMinMajorPoints
    int min_value = ui.spbMinMajorPoints->value();

    if (max_value < min_value)
        ui.spbMinMajorPoints->setValue(max_value);
}

void 
ControlWindow::on_spbMinSmoothPoints_valueChanged(int min_value)
{
    // Slot for change value signal from spbMaxSmoothPoints
    int max_value = ui.spbMaxSmoothPoints->value();

    if (min_value > max_value)
        ui.spbMaxSmoothPoints->setValue(min_value);
}

void
ControlWindow:: on_spbMaxSmoothPoints_valueChanged(int max_value)
{
    // Slot for change value signal from spbMinSmoothPoints
    int min_value = ui.spbMinSmoothPoints->value();

    if (max_value < min_value)
        ui.spbMinSmoothPoints->setValue(max_value);
}

void 
ControlWindow::on_dspbMinRoundQuality_valueChanged(double min_value)
{
    // Slot for change value signal from dspbMaxRoundQuality
    double max_value = ui.dspbMaxRoundQuality->value();

    if (min_value > max_value)
        ui.dspbMaxRoundQuality->setValue(min_value);
}

void 
ControlWindow::on_dspbMaxRoundQuality_valueChanged(double max_value)
{
    // Slot for change value signal from dspbMinRoundQuality
    double min_value = ui.dspbMinRoundQuality->value();

    if (max_value < min_value)
        ui.dspbMinRoundQuality->setValue(max_value); 
}

void 
ControlWindow::on_btnGeneratePolygon_clicked()
{
    // Slot for the click signal from btnGeneratePolygon
    // Get values from the control window
    u32 min_num_major_points = ui.spbMinMajorPoints->value();
    u32 max_num_major_points = ui.spbMaxMajorPoints->value();
    u32 min_num_smooth_points = ui.spbMinSmoothPoints->value();
    u32 max_num_smooth_points = ui.spbMaxSmoothPoints->value();
    f32 min_round_quality = ui.dspbMinRoundQuality->value();
    f32 max_round_quality = ui.dspbMaxRoundQuality->value();
    
    // Generate a new polygon and then request the drawing_window update
    this->drawing_window->smooth_polygon->randomizeSmoothPolygon(min_num_major_points, 
        max_num_major_points, min_num_smooth_points, max_num_smooth_points, 
        min_round_quality, max_round_quality);
    this->drawing_window->smooth_polygon->calcPoints();
    this->drawing_window->requestUpdate();
}

void
ControlWindow::closeEvent(QCloseEvent *event)
{
    // Method to for handling the window close procedure
    if (this->drawing_window)
    {
        this->drawing_window->destroy();
        this->drawing_window = nullptr; 
    }
    event->accept();
}