#ifndef RTSCENE_H
#define RTSCENE_H

#include <QDataStream>
#include <QVector>
#include <QImage>
#include "objects/objectsCommon.h"
#include "lights/lightsCommon.h"
#include "materials/materialsCommon.h"
#include "textures/textureCommon.h"
#include "kdtree/rtkdtree.h"

#define __CURRENT_VERSION 1.0f

//! Класс сцены

//! Содержит все необходимое для рассчета сцены и получения двумерного изображения методом трассировки лучей
class rtScene
{
private:
    //! Версия структуры сцены
    static constexpr float version = __CURRENT_VERSION;
    //! Максимальная глубина рекурсии при вычислении цвета пикселя.
    static const int recursionMaximumDepth = 7;
    //! Текстура неба
    rtTexture * skyMapTexture;
    //! Цвет освещения окружения
    Color3 ambientEnvColor;
    //! кД-Дерево
    rtkdTree objectsTree;
    //! Вектор объектов
    QVector<rtObject*> objectList;
    //! Вектор источников света
    QVector<rtLight*> lightList;
    //! Функция расчета луча
    Color3 castRay(rayf ray, int level, bool preview) const;
    //! Угол обзора наблюдателя
    float perspective_angle;
    //! Позиция наблюдателя
    vertex3f observer_pos;
    //! Точка наблюдения
    vertex3f spot_pos;
    //! Вертикальное направление
    vertex3f up_vector;
public:
    //! Функция получения отрендеренного изображения сцены
    QImage getImage(int w, int h, bool preview) const;
    //! Конструктор по умолчанию
    rtScene();
    //! Конструктор по имени файла содержимого
    rtScene(QString filename);
    //! Установка позиции наблюдателя
    void setObserver(vertex3f observer) { observer_pos = observer;}
    //! Установка позиции точки наблюдения
    void setSpot (vertex3f spot) {spot_pos = spot;}
    //! Сохранение текущего состояния сцены в файл
    void save(QString filename) const;
    //! Загрузка состояния сцены из файла
    void load(QString filename);
};

#endif // RTSCENE_H
