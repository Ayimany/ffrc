#include "PIDController.hh"

namespace ffrc {
    
    namespace builders {

        namespace pid {

            PIDController* PIDController::P(double value) {
                this -> p = value;
            	return this;
			}

            PIDController* PIDController::I(double value) {
                this -> i = value;
            	return this;
			}

            PIDController* PIDController::D(double value) {
                this -> d = value;
            	return this;
			}

            PIDController* PIDController::Tolerance(double value) {
                this -> tolerance = value;
                return this;
            }

            PIDController* PIDController::ClampThreshold(util::Threshold value) {
                this -> clampThreshold = value;
            	return this;
			}

            PIDController* PIDController::ContinuousOutputRange(util::Threshold value) {
                this -> CIR = value;
            	return this;
			}

            PIDController* PIDController::WithContinuousOutputRange() {
                this -> enableCIR = true;
            	return this;
			}

            PIDController* PIDController::OnReadInput(std::function<double()> value) {
                this -> onReadInput = value;
            	return this;
			}

            PIDController* PIDController::OnFeedOutput(std::function<void(double)> value) {
                this -> onFeedOutput = value;
            	return this;
			}

            systems::pid::PIDController PIDController::Build() {
                std::unique_ptr<frc2::PIDController> controllerimpl = std::make_unique<frc2::PIDController>(p, i, d);  
                systems::pid::PIDController controller{std::move(controllerimpl)};

                controller.SetTolerance(tolerance);

                controller.SetOutputFeedAction(onFeedOutput);
                controller.SetInputReadAction(onReadInput);

                controller.SetClampThreshold(clampThreshold);

                controller.SetContinuousInputRange(CIR);

                if (enableCIR) {
                    controller.EnableContinuousInputRange();
                }

                return controller;
                
            }

        }

    }

}