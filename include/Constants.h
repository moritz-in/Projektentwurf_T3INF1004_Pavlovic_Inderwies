#ifndef CONSTANCE_H
#define CONSTANCE_H
#include <opencv2/core/types.hpp>

namespace Constants {
    inline cv::Scalar BLUE = cv::Scalar(255, 0, 0);
    inline cv::Scalar RED = cv::Scalar(0, 0, 255);
    inline cv::Scalar GREEN = cv::Scalar(0, 255, 0);

    inline std::string FaceGame = "Reaktionsspiel";
    inline std::string GameOver = "Spiel-Ende!";
    inline std::string Score = "Punktzahl: ";
    inline std::string Player = "Spieler: ";

};

#endif //CONSTANCE_H
