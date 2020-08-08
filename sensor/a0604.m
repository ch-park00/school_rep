%% load data
clear; clc;
load('DeadReckoning_data.mat');
RL = exp1_014.Y(4).Data;
RR = exp1_014.Y(5).Data;
gpsX = exp1_014.Y(11).Data - exp1_014.Y(11).Data(1);
gpsY = exp1_014.Y(12).Data - exp1_014.Y(12).Data(1);
Yaw_rate = exp1_014.Y(9).Data;
Time = exp1_014.X.Data;

%% clac yaw_drift
yaw_mean = mean(Yaw_rate(1:5944));

%% initial Variable
x(1) = 0;
y(1) = 0;
th(1) = deg2rad(230);
vk = (RL+RR)/2/3.6;
wk = deg2rad(Yaw_rate - yaw_mean);

%% Display GPS
figure();
plot(gpsX, gpsY);
title('GPS Localization');

%% Dead Reckoning Using Eular

Ts(1) = 0.001;
for i = 2:length(Time)
    Ts(i) = Time(i) - Time(i-1);
end

x_1(1) = 0;
y_1(1) = 0;
th_1(1) = deg2rad(230);
vk_1 = (RL+RR)/2/3.6;
wk_1 = deg2rad(Yaw_rate - yaw_mean);

for k = 1:length(Time)
    x_1(k+1) = x_1(k) + vk_1(k) * Ts(k) * cos(th_1(k));
    y_1(k+1) = y_1(k) + vk_1(k) * Ts(k) * sin(th_1(k));
    th_1(k+1) = th_1(k) + (wk_1(k) * Ts(k));
end

% figure(); plot(x_1, y_1);
% title('Eular dead Reckoning');

%% Dead Reckoning Using 2nd Order Runge-Kutta

x_2(1) = 0;
y_2(1) = 0;
th_2(1) = deg2rad(230);
vk_2 = (RL+RR)/2/3.6;
wk_2 = deg2rad(Yaw_rate - yaw_mean);

for k = 1:length(Time)
    x_2(k+1) = x_2(k) + vk_2(k) * Ts(k) * cos(th_2(k) + (wk_2(k) * Ts(k)/2));
    y_2(k+1) = y_2(k) + vk_2(k) * Ts(k) * sin(th_2(k) + (wk_2(k) * Ts(k)/2));
    th_2(k+1) = th_2(k) + (wk_2(k) * Ts(k));
end

% figure(); plot(x_2, y_2);
% title('Runge-kutta Dead Reckoning');

%% Dead Reckoning Using Exact

x_3(1) = 0;
y_3(1) = 0;
th_3(1) = deg2rad(230);
vk_3 = (RL+RR)/2/3.6;
wk_3 = deg2rad(Yaw_rate - yaw_mean);

for k = 1:length(Time)
    th_3(k+1) = th_3(k) + (wk_3(k) * Ts(k));
    x_3(k+1) = x_3(k) + vk_3(k)/wk_3(k)*(sin(th_3(k+1)) - sin(th_3(k)));
    y_3(k+1) = y_3(k) - vk_3(k) / wk_3(k)*(cos(th_3(k+1)) - cos(th_3(k)));
end

% figure(); plot(x_3, y_3);
% title('Exact Dead Reckoning');

%% Display All

figure(); hold on;

plot(gpsX, gpsY, 'r-', 'LineWidth', 2.5);
plot(x_1, y_1, 'g-', 'LineWidth', 3);
plot(x_2, y_2, 'm-','LineWidth', 2);
plot(x_3, y_3, 'k-');

axis equal;
legend('GPS', 'Euler', 'Runge-Kutta', 'Exact');