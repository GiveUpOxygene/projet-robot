#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "useful.h"

/*
On travaille dans un repère orthoNormé d'origine le premier sommet de la pièce et de base x = (1, 0), y = (0, 1) selon hubert (donc y va devant le robot et x à sa droite)
De plus les unité utilisé seront le centimètre!
*/

typedef struct Segment Segment;
struct Segment
{
    Vector2 A; Vector2 B;
};

//Renvoie true si les 2 segment sont presque collinéaire, false sinon;
bool IsCollinear(Vector2* a, Vector2* b)
{
    return fabsf((b->x / a->x)) - fabsf((b->y / a->y)) < 0.03 * fabsf(b->y / a->y);
}

//Renvoie true si les 2 segment sont presque parallèle, false sinon;
bool IsParallele(Segment* seg1, Segment* seg2)
{
    Vector2* v1; Vector2* v2;
    Vector2 a = SubVector2(&(seg1->B), &(seg1->A), v1);
    Vector2 b = SubVector2(&(seg2->B), &(seg2->A), v2);
    return !IsCollinear(&a, &b);
}

// Renvoie le segment passant à peu près par tout les points(coor cartésien) de la liste points, seg doit etre vide au début de la fonction mais pas null
Segment* ToSegment(const Vector2 points[], int length, Segment* seg)
{
    //On fait l'algorithme de régression linéaire
    float sumX = 0;
    float sumY = 0;
    float sumXX = 0;
    float SumXY = 0;
    int indexXMin = 0;
    int indexXMax = 0;
    for (int i = 0; i < length; i++)
    {
        sumX += points[i].x;
        sumY += points[i].y;
        sumXX = points[i].x * points[i].x;
        SumXY = points[i].x * points[i].y;
        if(points[i].x < indexXMin)
        {
            indexXMin = i;
        } 
        else if(points[i].x > indexXMax)
        {
            indexXMax = i;
        }
    }
    //On calcule la moyenne des coefficients directeurs
    float avgSlope = ((length * SumXY) - (sumX * sumY)) / ((length * sumXX) - (sumX * sumX));
    //On calcule l'ordonnée à l'origine b
    float b = (sumY - (avgSlope * sumX)) / length;
    //On calcule les 2 points d'extrémité du segment
    Vector2 A = { points[indexXMin].x, avgSlope * points[indexXMin].x + b };
    Vector2 B = { points[indexXMax].x, avgSlope * points[indexXMax].x + b };
    seg->A = A;
    seg->B= B;
    return seg;
}

//Renvoie l'équation de la droite (y = ax + b ou a = equation.x et b = equation.y) dirigé par le segment segment, equation doit etre vide mais non nul <=> malloc a faire avant d'appeler la fonction
void GetSegmentEquation(const Segment* segment, Vector2* equation)
{
    equation->x = (segment->B.y - segment->A.y) / (segment->B.x - segment->A.x);
    equation->y = segment->A.y - equation->x * segment->A.x;
}

//Renvoie true si la droite (OP) intersect le segment seg
bool CollideSegmentDroite(const Segment* seg, const Vector2* O, const Vector2* P)
{
    Vector2 OP = SubVector2(P, O, &OP);
    Vector2 OB = SubVector2(&seg->B, O, &OB);
    Vector2 OA = SubVector2(&seg->A, O, &OA);
    return (OP.x * OB.y - OP.y * OB.x) * (OP.x * OA.y - OP.y * OA.x) < 0;
}

//Renvoie true si les 2 segments s'intersect
bool CollideSegments(const Segment* seg1, const Segment* seg2)
{
    return CollideSegmentDroite(seg1, &(seg2->A), &(seg2->B)) && CollideSegmentDroite(seg2, &(seg1->A), &(seg2->B));
}

//Renvoie true si les 2 segment s'intersectionne en plus des coordonnées du point d'intersection, renvoie false et (0, 0) si les 2 segment de se croise pas
bool Intersect(const Segment* seg1, const Segment* seg2, Vector2* intersectionPoint)
{
    if(!CollideSegments(seg1, seg2))//pas la peine de de continuer si les 2 segments ne se coupe pas
    {
        intersectionPoint->x = 0;
        intersectionPoint->y = 0;
        return false;
    }
    //On récupère les équations des 2 segments
    Vector2* eq1 = (Vector2*)malloc(sizeof(Vector2));
    Vector2* eq2 = (Vector2*)malloc(sizeof(Vector2));
    GetSegmentEquation(seg1, eq1);
    GetSegmentEquation(seg2, eq2);
    //On calcule la solution de l'intersection entre 2 droites de vecteur directeur seg1 et seg2
    intersectionPoint->x = (eq2->y - eq1->y) / (eq1->x - eq2->x);
    intersectionPoint->y = ((eq1->x * intersectionPoint->x + eq1->y) + (eq2->x * intersectionPoint->x + eq2->y)) / 2;
    free(eq1);
    free(eq2);
    return true;
}

char* BoolToString(bool b)
{
    return (char*)( b ? "true" : "false");
}