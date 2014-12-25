#ifndef RTMATERIAL_H
#define RTMATERIAL_H

#include "utils/utilsCommon.h"
#include "textures/textureCommon.h"
#include "lights/lightsCommon.h"
#include <QByteArray>
#include <QVector>
//! Класс материалов

//! Содержит методы и свойства для всех материалов, используемых в сцене
class rtMaterial {
public:
    //! Модель освещения объекта
    enum lightningModel {
        LAMBERT = 0, //!< Только фоновое
        PHONG, //!< Фоновое с бликами
        BLINN, //!< Не реализовано
        WARD, //!< Не реализовано
        NAYAR //!< Не реализовано
    };

    //! Получить номер материала
    int getID() const {
        return materialGlobalArrayIndex;
    }

    //! Конструктор по умолчанию
    rtMaterial();

    //! Полный конструктор объекта
    rtMaterial(
            //! Имя материала
            QString new_name = QString("Material"),
            //! Цвет рассеивания материала
            rtTexture *new_diffuse_color = new rtSolidColorTexture(colorDarkGray),
            //! Фоновый цвет
            rtTexture *new_ambient_color = new rtSolidColorTexture(colorBlack),
            //! Цвет бликов
            rtTexture *new_specular_color = new rtSolidColorTexture(colorWhite),
            //! Жесткость бликов
            float new_shininess = DEFAULT_SHININESS,
            //! Текстура отражения
            rtTexture *new_reflection_color = 0,
            //! Флаг отражения
            bool new_reflection_flag = false,
            //! Текстура преломления
            rtTexture *new_refraction_color = 0,
            //! Флаг преломления
            bool new_refraction_flag = false,
            //! Текстура коэфициента преломления
            rtTexture *new_IoR = 0,
            //! Множитель текстуры
            float new_IoR_multiplier = 1,
            //! Карта нормалей
            rtTexture *new_bumpMap_texture = 0,
            //! Множитель карты нормалей
            float new_bump_multiplier = 30,
            //! Флаг изменения нормалей
            bool new_bump_flag = false,
            //! Модель освещения
            lightningModel new_lModel = PHONG);

    //! Вычисление модели освещения
    Color3 computeColor(vertex3f, vertex3f, rayf, QVector<rtLight *> availableLightList, vertex3f center, Color3 ambientEnvColor) const;

    //! Вычисление результирущего цвета
    Color3 combineColor(Color3 lightColor, Color3 reflection, Color3 refraction) const;

    //! Флаг отражения
    bool refractionEnabled() const {
        return refraction_flag;
    }

    //! Флаг преломления
    bool reflectionEnabled() const {
        return reflection_flag;
    }

    //! Функция изменения нормали
    vertex3f remapNormal(vertex3f old_normal) const;

private:
    //! Стандартное значение жесткости блика
    static constexpr float DEFAULT_SHININESS = 20.0f;
    //! Стандартное значение коэфициента преломления
    static constexpr float DEFAULT_IOR = 1.5f;
    //! Стандартное значение множителя карты нормалей
    static constexpr float DEFAULT_BUMP = 0.5f;
    //! Фоновая текстура
    rtTexture *ambient_color;
    //! Диффузная текстура
    rtTexture *diffuse_color;
    //! Текстура бликов
    rtTexture *specular_color;
    //! Жесткость бликов
    float shininess;
    //! Текстура отражения
    rtTexture *reflection_color;
    //! Флаг отражения
    bool reflection_flag;
    //! Текструа преломления
    rtTexture *refraction_color;
    //! Флаг преломления
    bool refraction_flag;
    //! Текстура коэфициента преломления
    rtTexture *IoR;
    //! Множитель текстуры коэфициента преломления
    float IoR_multiplier;
    //! Карта нормалей
    rtTexture *bumpMap_texture;
    //! Множитель карты нормалей
    float bump_multiplier;
    //! Флаг изменения нормали
    bool bump_flag;
    //! Модель освещения
    lightningModel lModel;
    //! Название материала
    QString name;

    //! Функция сериализации экземпляра класса в строку
    QDataStream &toString(QDataStream &) const;

    //! Глобальный массив материалов
    static QVector<rtMaterial *> materialGlobalArray;
    //! Индекс в массиве материалов
    int materialGlobalArrayIndex;
};

#endif // RTMATERIAL_H
