cmake_minimum_required(VERSION 3.14.6)

# Opencv test case
include(../opencv_test_case.cmake)

make_test_case_opencv(OCV_PERSPECTIVE ./perspective.cpp)
make_test_case_opencv(OCV_LF_MATCHING_BRUTEFORCE_HAMMING ./lf_matching_bruteforce_hamming.cpp)
make_test_case_opencv(OCV_FIND_HOMOGRAPHY_WITH_LF_MATCHING ./find_homography_with_lf_matching.cpp)