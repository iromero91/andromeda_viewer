#include "geometry.h"

/**
 * @brief Angle
 * Calculate the angle between two points
 * @param pTo
 * @param pFrom
 * @return
 */
double Angle(QPointF pTo, QPointF pFrom)
{
    QPointF delta = pTo - pFrom;

    return qAtan2(delta.y(), delta.x());
}

/**
 * @brief DistanceSquared
 * Calculate the square of the distance between two points
 * @param pTo
 * @param pFrom
 * @return
 */
double DistanceSquared(QPointF pTo, QPointF pFrom)
{
    QPointF delta = pTo - pFrom;

    return qPow(delta.x(), 2) + qPow(delta.y(), 2);
}

/**
 * @brief Distance
 * Calculate the linear distance between two points
 * @param pTo
 * @param pFrom
 * @return
 */
double Distance(QPointF pTo, QPointF pFrom)
{
    return qSqrt(DistanceSquared(pTo, pFrom));
}

/**
 * @brief Midpoint
 * Calculate the midpoint between two points
 * @param pTo
 * @param pFrom
 * @return the midpoint (QPointF)
 */
QPointF Midpoint(QPointF pTo, QPointF pFrom)
{
    return QPointF((pTo.x() + pFrom.x()) / 2,
                   (pTo.y() + pFrom.y()) / 2);
}

/**
 * @brief ArcAngle
 * Calculate the angle of an arc given the chord length and the radius
 * Note: If the specified chordLength is greater than the diameter, an arc cannot be formed
 * @param radius
 * @param chordLength
 * @return
 */
double ArcAngle(double radius, double chordLength)
{
    // Return zero if the parameters are incompatible
    if (qFabs(radius) <= (chordLength / 2)) return 0;

    return 2 * qAsin(chordLength / (2 * radius));
}

/**
 * @brief ArcRadius
 * Return the radius of an arc segment given the angle and chordLength
 * @param angle
 * @param chordLength
 * @return
 */
double ArcRadius(double angle, double chordLength)
{
    return chordLength / 2 / qSin(angle / 2);
}

/**
 * @brief ArcLength
 * Calculate the length of an arc given the radius and angle
 * @param radius
 * @param angle
 * @return
 */
double ArcLength(double radius, double angle)
{
    return radius * angle;
}

/**
 * @brief ArcIsStraight
 * Determine if an arc segment is "straight" based on the provided angle
 * Straight segments have an angle equal (or close to) either zero (or) PI (180 degrees)
 * @param angle is the angle of the arc segment
 * @param threshold is used for floating real number comparison
 * @return true if the segment is straight else false
 */
bool ArcIsStraight(double angle, double threshold)
{
    if (qFabs(angle) < threshold)
        return true;

    if (qFabs(angle) > (M_PI - threshold))
        return true;

    return false;
}

bool ArcIsCurved(double angle, double threshold)
{
    return !ArcIsStraight(angle, threshold);
}