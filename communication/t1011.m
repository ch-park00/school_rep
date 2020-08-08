%% 
Fs = 1000; Ts = 1/Fs; % sampling frequency, period
fc = 10; % carrier frequency
t = 0:Ts:1.2; % time
m = sin(2*pi*t); % message signal
c = cos(2*pi*fc*t); % carrier signal
% modulation index: 1, 0.5, 0.2
X = [(1+m).*c; (1+0.5*m).*c; (1+0.2*m).*c]';
figure; plot(t', X, 'LineWidth', 2 );
hold on; plot( [0 1.2], [0 0], 'r-');
axis off; hold off;
ylim([-1 1]*2.1 );
L = legend('$a=1.0$', '$a=0.5$', '$a=0.2$'); % 범례
L.Interpreter = 'latex'; %매트랩은 오브젝트 언어
 
%%