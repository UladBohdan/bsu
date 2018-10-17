cd ~/build-appa-Desktop_Qt_5_8_0_GCC_64bit-Default/
./app --mode=cli \
--cli_mode=open \
--project_path=/home/parallels/projects/swiss-church/ \
--action=reconstruction \
--shared_calibration=true \
--use_camera_intrinsics_prior=false \
--intrinsics_to_optimize="focal,raddist"
