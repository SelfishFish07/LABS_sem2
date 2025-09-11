#include <stdio.h>
#include <stdlib.h>
#include<cmath>
#include <numbers>

#include "ans_handler.hpp"
#include "my_math.hpp"

AnswerHandler my_sin(double x){
    AnswerHandler answer;
    double result = 0;
    for (int i = 0; i<=10; ++i){
        result += std::pow(-1,i)*std::pow(x,2*i+1)/std::tgamma(2*i+2);
    }
    answer.value=x;
    answer.func=result;
    return answer;
}

AnswerHandler my_cos(double x){
    AnswerHandler answer;
    double result = 0;
    for (int i = 0; i<=10; ++i){
        result += std::pow(-1,i)*std::pow(x,2*i)/std::tgamma(2*i+1);
    }
    answer.value=x;
    answer.func=result;
    return answer;
}

AnswerHandler my_tg(double x){
    AnswerHandler answer;
    double result = my_sin(x).func/my_cos(x).func;
    answer.value=x;
    answer.func=result;
    return answer;
}

AnswerHandler my_ctg(double x){
    AnswerHandler answer;
    double result = my_cos(x).func/my_sin(x).func;
    answer.value=x;
    answer.func=result;
    return answer;
}

AnswerHandler my_arcsin(double x){
    AnswerHandler answer;
    double result = 0;
    for (int i = 0; i<=10; ++i){
        result += std::tgamma(2*i+1)*std::pow(x,2*i+1)/(std::pow(4,i)*std::tgamma(i+1)*std::tgamma(i+1)*(2*i+1));
    }
    answer.value=x;
    answer.func=result;
    return answer;
}

AnswerHandler my_arccos(double x){
    AnswerHandler answer;
    double result = std::numbers::pi/2-my_arcsin(x).func;
    answer.value=x;
    answer.func=result;
    return answer;
}

AnswerHandler my_arctg(double x){
    AnswerHandler answer;
    double result = 0;
    for (int i = 1; i<=10; ++i){
        result += std::pow(-1,i-1)*std::pow(x,2*i-1)/(2*i-1);
    }
    answer.value=x;
    answer.func=result;
    return answer;
}

AnswerHandler my_arcctg(double x){
    AnswerHandler answer;
    double result = std::numbers::pi/2-my_arctg(x).func;
    answer.value=x;
    answer.func=result;
    return answer;
}