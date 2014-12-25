#include "filters.h"

QImage filters::mean(const QImage & src){
	QImage result(src.width(),src.height(),QImage::Format_ARGB32);
	#pragma omp parallel for
	for (int x = 0; x < src.width(); x++)
		{
		#pragma omp parallel for
			for (int y = 0; y < src.height(); y++)
			{
				double sum=0;
				QImage kernel = src.copy(x-7,y-7,15,15);
				for (int kx = 0; kx < 15; kx++)
				{
					for (int ky = 0; ky < 15; ky++)
						sum += qGray(kernel.pixel(kx,ky));
				}
				sum /= 225.0;
				result.setPixel(x,y,
								qRgb(
										sum,
										sum,
										sum
										));
			}
		}
	return result;
}

QImage filters::adj(const QImage & src)
{
	QImage result = src.copy();
	return result;
}



