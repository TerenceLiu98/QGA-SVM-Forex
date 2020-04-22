clear;
clc;

%% a test programme && of libsvm's svmtrain & svmpredict %%
[heart_scale_label, heart_scale_inst] = libsvmread('heart_scale');
cmd = ('-c 1 -g 0.07');
model = libsvmtrain(heart_scale_label, heart_scale_inst, cmd);
[predict_label, accuracy, dec_values] = svmpredict(heart_scale_label, heart_scale_inst, model);

%% What is SVM %%
% SVM is a classification method by finding a optimized hyperplane,
% so that two types of samples can get the best classification effect
% under this hyperplane
% if the data is non-linear, SVM may map the data into a higher-dimension
% space as the core of SVM is to seperate data by using a lower-dimension
% line.