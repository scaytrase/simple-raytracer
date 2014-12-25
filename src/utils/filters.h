#ifndef FILTERS_H
#define FILTERS_H

#include <QVector>
#include <QImage>
#include <math.h>

namespace filters{
	class mck
	{
		public:
			QVector<QVector<float> > data;
			int h;
			int w;
			double norm;

	};
	QImage mean(const QImage & src);
	QImage adj(const QImage & src);
}


#endif // FILTERS_H
