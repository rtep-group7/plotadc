#include "window.h"
#include <cmath>

Window::Window() : plot( QString("Example Plot") ), gain(1), count(0),
		   adc("/dev/spidev0.0",
		       SPI_CPHA | SPI_CPOL,
		       8,50000,10)
{
	// set up the gain knob
	knob.setValue(gain);

	// use the Qt signals/slots framework to update the gain -
	// every time the knob is moved, the setGain function will be called
	connect( &knob, SIGNAL(valueChanged(double)), SLOT(setGain(double)) );

	// set up the thermometer
	thermo.setFillBrush( QBrush(Qt::red) );
	thermo.setRange(0, 20);
	thermo.show();


	// set up the initial plot data
	for( int index=0; index<plotDataSize; ++index )
	{
		xData[index] = index;
		yData[index] = 0;
	}

	// make a plot curve from the data and attach it to the plot
	curve.setSamples(xData, yData, plotDataSize);
	curve.attach(&plot);

	plot.replot();
	plot.show();


	// set up the layout - knob above thermometer
	vLayout.addWidget(&knob);
	vLayout.addWidget(&thermo);

	// plot to the left of knob and thermometer
	hLayout.addLayout(&vLayout);
	hLayout.addWidget(&plot);

	setLayout(&hLayout);
}


void Window::timerEvent( QTimerEvent * )
{
  // read adc voltage reading across thermistor
  double inVal = static_cast<double>(adc.readValue());
  double R = 1000.0 / ((inVal / std::pow(2.0, 16.0)) + 0.2) - 1000.0;

  // use beta-equation to calculate temperature
  const double beta = 3499.0;
  const double R0 = 1000.0;
  const double T0 = 272.15 + 25.0;
  double kelvin = beta / log(R / (R0 * exp(-beta / T0)));
  double celsius = kelvin - 272.15;

	++count;

	// add the new input to the plot
	memmove( yData, yData+1, (plotDataSize-1) * sizeof(double) );
	yData[plotDataSize-1] = celsius;
	curve.setSamples(xData, yData, plotDataSize);
	plot.replot();

	// set the thermometer value
	thermo.setValue( inVal + 10 );
}


// this function can be used to change the gain of the A/D internal amplifier
void Window::setGain(double gain)
{
	// for example purposes just change the amplitude of the generated input
	this->gain = gain;
}
