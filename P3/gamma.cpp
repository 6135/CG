#define NUMBER_ELEMENTS(x) (sizeof(x)/sizeof(x[0]))

const float vertices[] = {
    -0.2597f,	-0.5955f,	0.0f,		//C 0
    -0.1266f,	-0.5500f,	0.0f,		//D 1
    -0.1234f,	 0.4494f,	0.0f,		//E 2
    -0.2521f,	 0.5695f,	0.0f,		//F 3
    -0.1233f,	 0.5693f,	0.0f,		//G 4
     0.3711f,	 0.5676f,	0.0f,		//H 5
     0.2069f,	 0.5086f,	0.0f,		//I 6
    -0.1153f,	 0.4797f,	0.0f,		//J 7
    -0.1078f,	 0.4924f,	0.0f,		//K 8
    -0.1008f,	 0.5011f,	0.0f,		//L 9
    -0.0927f,	 0.5067f,	0.0f,		//M 10
    -0.3237f,	 0.5696f,	0.0f,		//N 11
    -0.3238f,	 0.5461f,	0.0f,		//O 12
    -0.2523f,	 0.5399f,	0.0f,		//P 13 
    -0.3042f,	 0.5363f,	0.0f,		//Q 14
    -0.2911f,	 0.5258f,	0.0f,		//R 15
    -0.2802f,	 0.5152f,	0.0f,		//S 16
    -0.2716f,	 0.5034f,	0.0f,		//T 17
    -0.2620f,	 0.4879f,	0.0f,		//U 18
    -0.2528f,	 0.4617f,	0.0f,		//V 19
    -0.0821f,	 0.5090f,	0.0f,		//W 20
    -0.0680f,	 0.5092f,	0.0f,		//Z 21
     0.2415f,	 0.5013f,	0.0f,		//A1 22
     0.2696f,	 0.4887f,	0.0f,		//B1 23
     0.2972f,	 0.4679f,	0.0f,		//C1 24
     0.3158f,	 0.4456f,	0.0f,		//D1 25
     0.3320f,	 0.4133f,	0.0f,		//E1 26
     0.3411f,	 0.3694f,	0.0f,		//F1 27
     0.3482f,	 0.3266f,	0.0f,		//G1 28
     0.3901f,	 0.2976f,	0.0f,		//H1 29
     0.3511f,	 0.2976f,	0.0f,		//I1 30
     0.3711f,	 0.5901f,	0.0f,		//J1 31
     0.2440f,	 0.5737f,	0.0f,		//K1 32
     0.1302f,	 0.5684f,	0.0f,		//L1 33

//back points

    -0.2597f,	-0.5955f,	-0.05f,		//C 34
    -0.1266f,	-0.5500f,	-0.05f,		//D 35
    -0.1234f,	 0.4494f,	-0.05f,		//E 36
    -0.2521f,	 0.5695f,	-0.05f,		//F 37
    -0.1233f,	 0.5693f,	-0.05f,		//G 38
     0.3711f,	 0.5676f,	-0.05f,		//H 39
     0.2069f,	 0.5086f,	-0.05f,		//I 40
    -0.1153f,	 0.4797f,	-0.05f,		//J 41
    -0.1078f,	 0.4924f,	-0.05f,		//K 42
    -0.1008f,	 0.5011f,	-0.05f,		//L 43
    -0.0927f,	 0.5067f,	-0.05f,		//M 44
    -0.3237f,	 0.5696f,	-0.05f,		//N 45
    -0.3238f,	 0.5461f,	-0.05f,		//O 46
    -0.2523f,	 0.5399f,	-0.05f,		//P 47
    -0.3042f,	 0.5363f,	-0.05f,		//Q 48
    -0.2911f,	 0.5258f,	-0.05f,		//R 49
    -0.2802f,	 0.5152f,	-0.05f,		//S 50
    -0.2716f,	 0.5034f,	-0.05f,		//T 51
    -0.2620f,	 0.4879f,	-0.05f,		//U 52
    -0.2528f,	 0.4617f,	-0.05f,		//V 53
    -0.0821f,	 0.5090f,	-0.05f,		//W 54
    -0.0680f,	 0.5092f,	-0.05f,		//Z 55
     0.2415f,	 0.5013f,	-0.05f,		//A1 56
     0.2696f,	 0.4887f,	-0.05f,		//B1 57
     0.2972f,	 0.4679f,	-0.05f,		//C1 58
     0.3158f,	 0.4456f,	-0.05f,		//D1 59
     0.3320f,	 0.4133f,	-0.05f,		//E1 60
     0.3411f,	 0.3694f,	-0.05f,		//F1 61
     0.3482f,	 0.3266f,	-0.05f,		//G1 62
     0.3901f,	 0.2976f,	-0.05f,		//H1 63
     0.3511f,	 0.2976f,	-0.05f,		//I1 64
     0.3711f,	 0.5901f,	-0.05f,		//J1 65
     0.2440f,	 0.5737f,	-0.05f,		//K1 66
     0.1302f,	 0.5684f,	-0.05f,		//L1 67
};

const int index[] = {
    0, 1, 2, //t1
    0, 3, 2, //t2
    2, 4, 3, //t3
    4, 5, 6, //t4
    4, 7, 2, //t5
    4, 8, 7, //t6
    4, 9, 8, //t7
    4, 10, 9, //t8
    3, 11, 12, //t9
    12, 13, 14, //t10
    14, 15, 13, //t11
    15, 16, 13, //t12
    16, 17, 13, //t13
    17, 18, 13, //t14
    18, 19, 13, //t15
    10, 20, 4, //t16
    4, 21, 20, //t17
    6, 22, 5, //t19
    22, 23, 5, //t20
    23, 24, 5, //t21
    24, 25, 5, //t22
    25, 26, 5, //t23
    26, 27, 5, //t24
    27, 28, 5, //t25
    5, 29, 30, //t26
    28, 30, 5, //t27
    5, 31, 32, //t28
    32, 33, 5, //t29
    12, 3, 13, //t30
    4, 6, 21, //t31

// back triangles

    34, 35, 36, //t1
    34, 37, 36, //t2
    36, 38, 37, //t3
    38, 39, 40, //t4
    38, 41, 36, //t5
    38, 42, 41, //t6
    38, 43, 42, //t7
    38, 44, 43, //t8
    37, 45, 46, //t9
    46, 47, 48, //t10
    48, 49, 47, 
    49, 50, 47, 
    50, 51, 47, 
    51, 52, 47,
    52, 53, 47, 
    44, 54, 38,
    38, 55, 54,
    40, 56, 39, 
    56, 57, 39,
    57, 58, 39,
    58, 59, 39,
    59, 60, 39,
    60, 61, 39,
    61, 62, 39,
    39, 63, 64,
    62, 64, 39,
    39, 65, 66,
    66, 67, 39,
    46, 37, 47,
    38, 40, 55, 

    //depth


};
const int triangle_count = NUMBER_ELEMENTS(index);