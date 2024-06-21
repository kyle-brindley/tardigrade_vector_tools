/**
  * \file test_tardigrade_interp_ndCartesian.cpp
  *
  * Tests for tardigrade_interp_ndCartesian
  */

#include<vector>
#include<iostream>
#include<fstream>
#include<math.h>
#define USE_EIGEN
#include<tardigrade_interp_ndCartesian.h>

#define BOOST_TEST_MODULE test_tardigrade_interpNdCartesian
#include <boost/test/included/unit_test.hpp>
#include <boost/test/tools/output_test_stream.hpp>

#define DEFAULT_TEST_TOLERANCE 1e-6
#define CHECK_PER_ELEMENT boost::test_tools::per_element( )

typedef double floatType;
typedef std::vector< floatType > vectorType;
typedef std::vector< vectorType > matrixType;

void print( vectorType a ){
    /*!
     * Print the vector to the terminal
     */

    for ( unsigned int i=0; i<a.size( ); i++ ){
        std::cout << a[ i ] << " ";
    }
    std::cout << "\n";
}

void print( matrixType A ){
    /*!
     * Print the matrix to the terminal
     */

    for ( unsigned int i=0; i<A.size( ); i++ ){
        print( A[ i ] );
    }
}

vectorType getD( ){

    vectorType D = {
       -1.        ,  2.        ,  0.1       , -4.1       , -1.        ,
        2.        ,  0.4       , -4.4       , -1.        ,  2.        ,
        0.7       , -4.7       , -1.        ,  2.33333333,  0.1       ,
       -4.3962963 , -1.        ,  2.33333333,  0.4       , -4.6962963 ,
       -1.        ,  2.33333333,  0.7       , -4.9962963 , -1.        ,
        2.66666667,  0.1       , -4.47037037, -1.        ,  2.66666667,
        0.4       , -4.77037037, -1.        ,  2.66666667,  0.7       ,
       -5.07037037, -1.        ,  3.        ,  0.1       , -4.1       ,
       -1.        ,  3.        ,  0.4       , -4.4       , -1.        ,
        3.        ,  0.7       , -4.7       , -1.        ,  3.33333333,
        0.1       , -3.06296296, -1.        ,  3.33333333,  0.4       ,
       -3.36296296, -1.        ,  3.33333333,  0.7       , -3.66296296,
       -1.        ,  3.66666667,  0.1       , -1.13703704, -1.        ,
        3.66666667,  0.4       , -1.43703704, -1.        ,  3.66666667,
        0.7       , -1.73703704, -1.        ,  4.        ,  0.1       ,
        1.9       , -1.        ,  4.        ,  0.4       ,  1.6       ,
       -1.        ,  4.        ,  0.7       ,  1.3       , -0.55555556,
        2.        ,  0.1       , -2.32222222, -0.55555556,  2.        ,
        0.4       , -2.62222222, -0.55555556,  2.        ,  0.7       ,
       -2.92222222, -0.55555556,  2.33333333,  0.1       , -2.47037037,
       -0.55555556,  2.33333333,  0.4       , -2.77037037, -0.55555556,
        2.33333333,  0.7       , -3.07037037, -0.55555556,  2.66666667,
        0.1       , -2.3962963 , -0.55555556,  2.66666667,  0.4       ,
       -2.6962963 , -0.55555556,  2.66666667,  0.7       , -2.9962963 ,
       -0.55555556,  3.        ,  0.1       , -1.87777778, -0.55555556,
        3.        ,  0.4       , -2.17777778, -0.55555556,  3.        ,
        0.7       , -2.47777778, -0.55555556,  3.33333333,  0.1       ,
       -0.69259259, -0.55555556,  3.33333333,  0.4       , -0.99259259,
       -0.55555556,  3.33333333,  0.7       , -1.29259259, -0.55555556,
        3.66666667,  0.1       ,  1.38148148, -0.55555556,  3.66666667,
        0.4       ,  1.08148148, -0.55555556,  3.66666667,  0.7       ,
        0.78148148, -0.55555556,  4.        ,  0.1       ,  4.56666667,
       -0.55555556,  4.        ,  0.4       ,  4.26666667, -0.55555556,
        4.        ,  0.7       ,  3.96666667, -0.11111111,  2.        ,
        0.1       , -0.54444444, -0.11111111,  2.        ,  0.4       ,
       -0.84444444, -0.11111111,  2.        ,  0.7       , -1.14444444,
       -0.11111111,  2.33333333,  0.1       , -0.54444444, -0.11111111,
        2.33333333,  0.4       , -0.84444444, -0.11111111,  2.33333333,
        0.7       , -1.14444444, -0.11111111,  2.66666667,  0.1       ,
       -0.32222222, -0.11111111,  2.66666667,  0.4       , -0.62222222,
       -0.11111111,  2.66666667,  0.7       , -0.92222222, -0.11111111,
        3.        ,  0.1       ,  0.34444444, -0.11111111,  3.        ,
        0.4       ,  0.04444444, -0.11111111,  3.        ,  0.7       ,
       -0.25555556, -0.11111111,  3.33333333,  0.1       ,  1.67777778,
       -0.11111111,  3.33333333,  0.4       ,  1.37777778, -0.11111111,
        3.33333333,  0.7       ,  1.07777778, -0.11111111,  3.66666667,
        0.1       ,  3.9       , -0.11111111,  3.66666667,  0.4       ,
        3.6       , -0.11111111,  3.66666667,  0.7       ,  3.3       ,
       -0.11111111,  4.        ,  0.1       ,  7.23333333, -0.11111111,
        4.        ,  0.4       ,  6.93333333, -0.11111111,  4.        ,
        0.7       ,  6.63333333,  0.33333333,  2.        ,  0.1       ,
        1.23333333,  0.33333333,  2.        ,  0.4       ,  0.93333333,
        0.33333333,  2.        ,  0.7       ,  0.63333333,  0.33333333,
        2.33333333,  0.1       ,  1.38148148,  0.33333333,  2.33333333,
        0.4       ,  1.08148148,  0.33333333,  2.33333333,  0.7       ,
        0.78148148,  0.33333333,  2.66666667,  0.1       ,  1.75185185,
        0.33333333,  2.66666667,  0.4       ,  1.45185185,  0.33333333,
        2.66666667,  0.7       ,  1.15185185,  0.33333333,  3.        ,
        0.1       ,  2.56666667,  0.33333333,  3.        ,  0.4       ,
        2.26666667,  0.33333333,  3.        ,  0.7       ,  1.96666667,
        0.33333333,  3.33333333,  0.1       ,  4.04814815,  0.33333333,
        3.33333333,  0.4       ,  3.74814815,  0.33333333,  3.33333333,
        0.7       ,  3.44814815,  0.33333333,  3.66666667,  0.1       ,
        6.41851852,  0.33333333,  3.66666667,  0.4       ,  6.11851852,
        0.33333333,  3.66666667,  0.7       ,  5.81851852,  0.33333333,
        4.        ,  0.1       ,  9.9       ,  0.33333333,  4.        ,
        0.4       ,  9.6       ,  0.33333333,  4.        ,  0.7       ,
        9.3       ,  0.77777778,  2.        ,  0.1       ,  3.01111111,
        0.77777778,  2.        ,  0.4       ,  2.71111111,  0.77777778,
        2.        ,  0.7       ,  2.41111111,  0.77777778,  2.33333333,
        0.1       ,  3.30740741,  0.77777778,  2.33333333,  0.4       ,
        3.00740741,  0.77777778,  2.33333333,  0.7       ,  2.70740741,
        0.77777778,  2.66666667,  0.1       ,  3.82592593,  0.77777778,
        2.66666667,  0.4       ,  3.52592593,  0.77777778,  2.66666667,
        0.7       ,  3.22592593,  0.77777778,  3.        ,  0.1       ,
        4.78888889,  0.77777778,  3.        ,  0.4       ,  4.48888889,
        0.77777778,  3.        ,  0.7       ,  4.18888889,  0.77777778,
        3.33333333,  0.1       ,  6.41851852,  0.77777778,  3.33333333,
        0.4       ,  6.11851852,  0.77777778,  3.33333333,  0.7       ,
        5.81851852,  0.77777778,  3.66666667,  0.1       ,  8.93703704,
        0.77777778,  3.66666667,  0.4       ,  8.63703704,  0.77777778,
        3.66666667,  0.7       ,  8.33703704,  0.77777778,  4.        ,
        0.1       , 12.56666667,  0.77777778,  4.        ,  0.4       ,
       12.26666667,  0.77777778,  4.        ,  0.7       , 11.96666667,
        1.22222222,  2.        ,  0.1       ,  4.78888889,  1.22222222,
        2.        ,  0.4       ,  4.48888889,  1.22222222,  2.        ,
        0.7       ,  4.18888889,  1.22222222,  2.33333333,  0.1       ,
        5.23333333,  1.22222222,  2.33333333,  0.4       ,  4.93333333,
        1.22222222,  2.33333333,  0.7       ,  4.63333333,  1.22222222,
        2.66666667,  0.1       ,  5.9       ,  1.22222222,  2.66666667,
        0.4       ,  5.6       ,  1.22222222,  2.66666667,  0.7       ,
        5.3       ,  1.22222222,  3.        ,  0.1       ,  7.01111111,
        1.22222222,  3.        ,  0.4       ,  6.71111111,  1.22222222,
        3.        ,  0.7       ,  6.41111111,  1.22222222,  3.33333333,
        0.1       ,  8.78888889,  1.22222222,  3.33333333,  0.4       ,
        8.48888889,  1.22222222,  3.33333333,  0.7       ,  8.18888889,
        1.22222222,  3.66666667,  0.1       , 11.45555556,  1.22222222,
        3.66666667,  0.4       , 11.15555556,  1.22222222,  3.66666667,
        0.7       , 10.85555556,  1.22222222,  4.        ,  0.1       ,
       15.23333333,  1.22222222,  4.        ,  0.4       , 14.93333333,
        1.22222222,  4.        ,  0.7       , 14.63333333,  1.66666667,
        2.        ,  0.1       ,  6.56666667,  1.66666667,  2.        ,
        0.4       ,  6.26666667,  1.66666667,  2.        ,  0.7       ,
        5.96666667,  1.66666667,  2.33333333,  0.1       ,  7.15925926,
        1.66666667,  2.33333333,  0.4       ,  6.85925926,  1.66666667,
        2.33333333,  0.7       ,  6.55925926,  1.66666667,  2.66666667,
        0.1       ,  7.97407407,  1.66666667,  2.66666667,  0.4       ,
        7.67407407,  1.66666667,  2.66666667,  0.7       ,  7.37407407,
        1.66666667,  3.        ,  0.1       ,  9.23333333,  1.66666667,
        3.        ,  0.4       ,  8.93333333,  1.66666667,  3.        ,
        0.7       ,  8.63333333,  1.66666667,  3.33333333,  0.1       ,
       11.15925926,  1.66666667,  3.33333333,  0.4       , 10.85925926,
        1.66666667,  3.33333333,  0.7       , 10.55925926,  1.66666667,
        3.66666667,  0.1       , 13.97407407,  1.66666667,  3.66666667,
        0.4       , 13.67407407,  1.66666667,  3.66666667,  0.7       ,
       13.37407407,  1.66666667,  4.        ,  0.1       , 17.9       ,
        1.66666667,  4.        ,  0.4       , 17.6       ,  1.66666667,
        4.        ,  0.7       , 17.3       ,  2.11111111,  2.        ,
        0.1       ,  8.34444444,  2.11111111,  2.        ,  0.4       ,
        8.04444444,  2.11111111,  2.        ,  0.7       ,  7.74444444,
        2.11111111,  2.33333333,  0.1       ,  9.08518519,  2.11111111,
        2.33333333,  0.4       ,  8.78518519,  2.11111111,  2.33333333,
        0.7       ,  8.48518519,  2.11111111,  2.66666667,  0.1       ,
       10.04814815,  2.11111111,  2.66666667,  0.4       ,  9.74814815,
        2.11111111,  2.66666667,  0.7       ,  9.44814815,  2.11111111,
        3.        ,  0.1       , 11.45555556,  2.11111111,  3.        ,
        0.4       , 11.15555556,  2.11111111,  3.        ,  0.7       ,
       10.85555556,  2.11111111,  3.33333333,  0.1       , 13.52962963,
        2.11111111,  3.33333333,  0.4       , 13.22962963,  2.11111111,
        3.33333333,  0.7       , 12.92962963,  2.11111111,  3.66666667,
        0.1       , 16.49259259,  2.11111111,  3.66666667,  0.4       ,
       16.19259259,  2.11111111,  3.66666667,  0.7       , 15.89259259,
        2.11111111,  4.        ,  0.1       , 20.56666667,  2.11111111,
        4.        ,  0.4       , 20.26666667,  2.11111111,  4.        ,
        0.7       , 19.96666667,  2.55555556,  2.        ,  0.1       ,
       10.12222222,  2.55555556,  2.        ,  0.4       ,  9.82222222,
        2.55555556,  2.        ,  0.7       ,  9.52222222,  2.55555556,
        2.33333333,  0.1       , 11.01111111,  2.55555556,  2.33333333,
        0.4       , 10.71111111,  2.55555556,  2.33333333,  0.7       ,
       10.41111111,  2.55555556,  2.66666667,  0.1       , 12.12222222,
        2.55555556,  2.66666667,  0.4       , 11.82222222,  2.55555556,
        2.66666667,  0.7       , 11.52222222,  2.55555556,  3.        ,
        0.1       , 13.67777778,  2.55555556,  3.        ,  0.4       ,
       13.37777778,  2.55555556,  3.        ,  0.7       , 13.07777778,
        2.55555556,  3.33333333,  0.1       , 15.9       ,  2.55555556,
        3.33333333,  0.4       , 15.6       ,  2.55555556,  3.33333333,
        0.7       , 15.3       ,  2.55555556,  3.66666667,  0.1       ,
       19.01111111,  2.55555556,  3.66666667,  0.4       , 18.71111111,
        2.55555556,  3.66666667,  0.7       , 18.41111111,  2.55555556,
        4.        ,  0.1       , 23.23333333,  2.55555556,  4.        ,
        0.4       , 22.93333333,  2.55555556,  4.        ,  0.7       ,
       22.63333333,  3.        ,  2.        ,  0.1       , 11.9       ,
        3.        ,  2.        ,  0.4       , 11.6       ,  3.        ,
        2.        ,  0.7       , 11.3       ,  3.        ,  2.33333333,
        0.1       , 12.93703704,  3.        ,  2.33333333,  0.4       ,
       12.63703704,  3.        ,  2.33333333,  0.7       , 12.33703704,
        3.        ,  2.66666667,  0.1       , 14.1962963 ,  3.        ,
        2.66666667,  0.4       , 13.8962963 ,  3.        ,  2.66666667,
        0.7       , 13.5962963 ,  3.        ,  3.        ,  0.1       ,
       15.9       ,  3.        ,  3.        ,  0.4       , 15.6       ,
        3.        ,  3.        ,  0.7       , 15.3       ,  3.        ,
        3.33333333,  0.1       , 18.27037037,  3.        ,  3.33333333,
        0.4       , 17.97037037,  3.        ,  3.33333333,  0.7       ,
       17.67037037,  3.        ,  3.66666667,  0.1       , 21.52962963,
        3.        ,  3.66666667,  0.4       , 21.22962963,  3.        ,
        3.66666667,  0.7       , 20.92962963,  3.        ,  4.        ,
        0.1       , 25.9       ,  3.        ,  4.        ,  0.4       ,
       25.6       ,  3.        ,  4.        ,  0.7       , 25.3        };

    return D;

}

BOOST_AUTO_TEST_CASE( test_constructor, * boost::unit_test::tolerance( DEFAULT_TEST_TOLERANCE ) ){
    /*!
     * Test the function that extracts the size of each of the interpolation dimensions
     */

    vectorType D = getD( );

    const unsigned int spatial_dimension = 3;

    const unsigned int D_size = D.size( );

    const unsigned int npts   = D.size( ) / 4;

    std::vector< unsigned int > dimensions_answer = { 10, 7, 3 };

    std::vector< unsigned int > strides_answer = { 21, 3, 1 };

    tardigradeVectorTools::interp::ndCartesian interp( spatial_dimension, D.data( ), D_size, npts );

    BOOST_TEST( dimensions_answer == *interp.getDimensions( ), CHECK_PER_ELEMENT );

    BOOST_TEST( strides_answer == *interp.getStrides( ), CHECK_PER_ELEMENT );

}

BOOST_AUTO_TEST_CASE( test_eval, * boost::unit_test::tolerance( DEFAULT_TEST_TOLERANCE ) ){
    /*!
     * Test the function that extracts the size of each of the interpolation dimensions
     */

    vectorType D = getD( );

    const unsigned int spatial_dimension = 3;

    const unsigned int D_size = D.size( );

    const unsigned int npts   = D.size( ) / 4;

    std::vector< unsigned int > dimensions_answer = { 10, 7, 3 };

    std::vector< unsigned int > strides_answer = { 21, 3, 1 };

    std::vector< floatType > p_1 = { 0.3, 10.1, 0.0 };

    floatType answer_1 = 9.7;

    std::vector< unsigned int > current_bounds_answer_1 = { 2, 3, 6, 6, 0, 0 };

    std::vector< floatType > weights_answer_1 = { 0.075, 0.925, 0.5, 0.5, 0.5, 0.5 };

    std::vector< floatType > p_2 = { 0.3, 10.1, 0.5 };

    floatType answer_2 = 9.3;

    std::vector< unsigned int > current_bounds_answer_2 = { 2, 3, 6, 6, 1, 2 };

    std::vector< floatType > weights_answer_2 = { 0.075, 0.925, 0.5, 0.5, 0.66666667, 0.33333333 };

    tardigradeVectorTools::interp::ndCartesian interp( spatial_dimension, D.data( ), D_size, npts );

    BOOST_TEST( answer_1 == interp.eval( p_1 ) );

    BOOST_TEST( current_bounds_answer_1 == interp.getCurrentBounds( p_1, npts ), CHECK_PER_ELEMENT );

    BOOST_TEST( weights_answer_1 == *interp.getCurrentWeights( ), CHECK_PER_ELEMENT );

    BOOST_TEST( answer_2 == interp.eval( p_2 ) );

    BOOST_TEST( current_bounds_answer_2 == interp.getCurrentBounds( p_2, npts ), CHECK_PER_ELEMENT );

    BOOST_TEST( weights_answer_2 == *interp.getCurrentWeights( ), CHECK_PER_ELEMENT );

}
