#include "rtscene.h"
#include <iostream>
#include <qmath.h>
#include <omp.h>

rtScene::rtScene()
{
	spot_pos = vertex3d(0,0,2);
	perspective_angle = 65;

	skymap = new rtSolidColorTexture(colorBlack);//rtImageTexture("textures/sky-texture.jpg");
	vertex3d zero(0,0,0);
	sky = new rtSphereObject(zero,10000);
	ambientIntensity = 1;
}

bool rtScene::hitObject(rayd ray, int &object_id, double &distanse) const
{
	bool found=false;
	double inter;
	for (int i=0; i < objectList.size(); i++){
		if (objectList[i]->intersects(ray,inter))
		{
			if ( !found  ||inter < distanse  ){
				distanse = inter;
				object_id = i;
				found = true;
			}
		}
	}
	return found;

}

bool rtScene::justHit(rayd ray) const
{
	double inter;
	for (int i=0; i < objectList.size(); i++)
	{
		if (objectList[i]->intersects(ray,inter))
			return true;
	}
	return false;
}


Color3 rtScene::sendRay(rayd ray, int level) const
{

	if (level > maxlevel)
		return colorBlack;

	double rayLength=0;
	int nearestObjectID=-1;

	if ( !hitObject (
			ray,
			nearestObjectID,
			rayLength)
		)
		return skymap->getColorAt(sky->texCoord(ray.direction));

	vertex3d intersectionPoint  = ray.point + ray.direction*rayLength;
	vertex3d normalPoint  = ray.point + ray.direction*(rayLength-0.0001);
	vertex2d texturePoint		= objectList[nearestObjectID]->texCoord(intersectionPoint);
	vertex3d surfaceNormal      = objectList[nearestObjectID]->normal(normalPoint);
	surfaceNormal.normalize();

	Color3 result;

	//! Желаете ли просмотреть карту нормалей?
//	return Color3(1+surfaceNormal.x,1+surfaceNormal.y,1+surfaceNormal.z)/2;

	if (objectList[nearestObjectID]->material()->useBump())
	{
		Color3 bumpmap = objectList[nearestObjectID]->material()->bump(texturePoint);
		double bValue = objectList[nearestObjectID]->material()->bumpValue();
		vertex3d
				bumpVector(
						(bumpmap.r - 0.5f)*2.0f
						,(bumpmap.g - 0.5f)*2.0f
						,bValue*(bumpmap.b - 0.5f)*2.0f
						);
		bumpVector.normalize();
		vertex3d rV = zDirection.vector_mult(surfaceNormal);
		rV.normalize();
		double
				CaX = zDirection.dot_product_norm(surfaceNormal),
				SaX	= qSqrt(1-CaX*CaX);
		double
				xx=rV.x()*rV.x(),
				xy=rV.y()*rV.x(),
				yy=rV.y()*rV.y(),
				d=1-CaX;
		vertex3d
				r1 (
						CaX + d*xx	,
						d*xy	,
						-SaX*rV.y()
						),
				r2(
						d*xy	,
						CaX + d*yy,
						SaX*rV.x()
						),
				r3(
						SaX*rV.y(),
						-SaX*rV.x(),
						CaX
						);
		vertex3d newNormal =
				r1*bumpVector.x() +
				r2*bumpVector.y() +
				r3*bumpVector.z();

		surfaceNormal = newNormal;
		surfaceNormal.normalize();
	}


	Color3 pointColor = (objectList[nearestObjectID]->material()->ambient(texturePoint) * ambientIntensity);

	//Расчет освещения по модели Фонга (ambient + diffuse + specular)
	QVector<int> lights = availableLights(intersectionPoint);
	for (int i = 0; i < lights.size(); i++)
	{
		vertex3d lightPosition  = lightList[ lights[i] ]->getPosition();
		Color3   lightColor     = lightList[ lights[i] ]->getColor();
		double	 lightInensity  = lightList[ lights[i] ]->getIntensity();
		vertex3d lightDirection = (lightPosition - intersectionPoint);
		lightDirection.normalize();
		pointColor +=
				((objectList[nearestObjectID]->material()->diffuse(texturePoint) * lightColor) *
				 qMax(
						 lightDirection.dot_product_norm(surfaceNormal)
						 ,double(0)
						 ) *
				 lightInensity
				 )
				;

		vertex3d rL = (surfaceNormal*2*(lightDirection*surfaceNormal) - lightDirection);
		rL.normalize();
		pointColor +=
				(( (objectList[nearestObjectID]->material()->specular(texturePoint) * lightColor)

				   )*
				 pow (
						 qMax (
								 rL.dot_product_norm(  ray.direction *(-1)  )
								 ,double(0)
								 )
						 ,objectList[nearestObjectID]->material()->shiness() ) *
				 lightInensity);
	}

	Color3 objReflColor = objectList[nearestObjectID]->material()->reflection(texturePoint);

	Color3 reflectionColor =
			(objReflColor == colorBlack) ?
			colorBlack :
			sendRay(
					rayd(
							intersectionPoint,
							(ray.direction - surfaceNormal*2*(ray.direction*surfaceNormal) )),
					level+1);


	Color3 objRefrColor = objectList[nearestObjectID]->material()->refraction(texturePoint);
	Color3 refractionColor = colorBlack;
	if (objRefrColor != colorBlack)
	{
		// Via http://www.cs.unc.edu/~rademach/xroads-RT/RTarticle.html
		// Reflections and Refractions
		vertex3d
				sn = surfaceNormal*ray.direction < 0 ? surfaceNormal : surfaceNormal*(-1),
				rd = ray.direction;
		sn.normalize();
		rd.normalize();
		double
				inC1	= -( sn * rd ),
				n1		= 1, //index of refraction of original medium
				n2		= objectList[nearestObjectID]->material()->ior(), //index of refraction of new medium
				inN		= (inC1 > 0) ? n1 / n2 : n2 / n1,
//				outN	= n2 / n1,
				inC2	= qSqrt( qMax (1 - inN*inN * (1 - inC1*inC1),double (0)) );
//				crossDistanse;

		rayd ingoingRay(
				ingoingRay.point = intersectionPoint,
				ingoingRay.direction = (ray.direction * inN) +  surfaceNormal * (inN * inC1 - inC2)
									   );
		ingoingRay.direction.normalize();
//		if (objectList[nearestObjectID]->intersects(ingoingRay,crossDistanse)){
//			vertex3d outPoint	= ingoingRay.point + ingoingRay.direction*crossDistanse;
//			vertex3d outNormal	= objectList[nearestObjectID]->normal(outPoint);
//			outNormal.normalize();
//			double
//					outC1 = ( outNormal * ingoingRay.direction ),
//					outC2 = qSqrt( qMax (1 - outN*outN * (1 - outC1*outC1),double (0)) );
//			rayd outgoungRay(
//					outgoungRay.point		= outPoint,
//					outgoungRay.direction	=
//					(ingoingRay.direction * outN) +
//					outNormal * (outN * outC1 - outC2));

//			refractionColor = sendRay(outgoungRay,level+1);
//		} else
			refractionColor = sendRay(ingoingRay,level+1);

	}

	result = combineColors(
			pointColor,
			reflectionColor,
			refractionColor,
			objReflColor,
			objRefrColor
			);

	result.normalize();
	return result;

}


Color3 rtScene::combineColors(
		const Color3 &diffuse,
		const Color3 &reflection,
		const Color3 &refraction,
		const Color3 &RLC,
		const Color3 &RFC) const
{
	Color3 result;
	result = diffuse + RLC*reflection + RFC*refraction;
	return result;
}


QVector<int> rtScene::availableLights(vertex3d curpoint) const
{
	QVector<int> result;
	for (int i=0; i < lightList.size(); i++){
		rayd ray;
		ray.point = curpoint;
		ray.direction = lightList[i]->getPosition() - curpoint;
		ray.direction = ray.direction/ !ray.direction;
		bool clear=true;
		double inter;
		double dist;
		for (int obj = 0; obj < objectList.size(); obj++){
			if (qAbs(objectList[obj]->material()->ior() - 1) < 1e-2) continue;
			if (objectList[obj]->intersects(ray,inter))
			{
				dist = !(lightList[i]->getPosition() - curpoint);
				if ( inter  < dist)
				{
					clear = false;
					break;
				}
			}
		}
		if (clear) result.append(i);
	}
	return result;
}

void rtScene::setObserver(vertex3d newObserver)
{
	observer_pos = newObserver;
}

void rtScene::setSpot(vertex3d spot)
{
	spot_pos = spot;
}

Color3 rtScene::sendPreviewRay(rayd ray) const
{
	Color3 result(0,0,0);
	double rayLength=0;
	int nearestObjectID=-1;

	if ( !hitObject (
			ray,
			nearestObjectID,
			rayLength)
		)
		return result;

	vertex3d intersectionPoint  = ray.point + ray.direction*rayLength;
	vertex3d normalPoint  = ray.point + ray.direction*(rayLength-0.0001);
	vertex2d texturePoint		= objectList[nearestObjectID]->texCoord(intersectionPoint);
	vertex3d surfaceNormal      = objectList[nearestObjectID]->normal(normalPoint);
	surfaceNormal.normalize();
//	return Color3(1+surfaceNormal.x,1+surfaceNormal.y,1+surfaceNormal.z)/2;
	// Расчет фонового освещения
	result = (objectList[nearestObjectID]->material()->ambient(texturePoint) *
			  ambientIntensity);
	//Расчет освещения по модели Фонга (ambient + diffuse + specular)
	QVector<int> lights = availableLights(intersectionPoint);
	for (int i = 0; i < lights.size(); i++)
	{
		vertex3d lightPosition  = lightList[ lights[i] ]->getPosition();
		Color3   lightColor     = lightList[ lights[i] ]->getColor();
		double	 lightInensity  = lightList[ lights[i] ]->getIntensity();
		vertex3d lightDirection = (lightPosition - intersectionPoint);
		lightDirection.normalize();
		result +=
				((objectList[nearestObjectID]->material()->diffuse(texturePoint) * lightColor) *
				 qMax(
						 lightDirection.dot_product_norm(surfaceNormal)
						 ,double(0)
						 ) *
				 lightInensity
				 )
				;
	}

	result.normalize();
	return result;
}

void rtScene::loadObjectList(QVector<rtObject *> newObjectList)
{
    objectList.clear();
    for (int i = 0; i < newObjectList.count(); i++)
    objectList.append(newObjectList.at(i));
}

void rtScene::loadLightList(QVector<rtLight *> newLightList)
{
    lightList.clear();
    for (int i = 0; i < newLightList.count(); i++)
    lightList.append(newLightList.at(i));
}
