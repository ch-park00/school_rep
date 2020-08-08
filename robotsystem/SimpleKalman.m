%%
function volt=SimpleKalman(z)

persistent A H Q R
persistent x P
persistent firstRun

if isempty(firstRun)
    % 초기값 설정
    A=1;H=1;Q=0;R=4;
    x=14;P=6;
    
    firstRun=1;
end
% 추정값 예측
xp=A*x;
% 오차 공분산 예측
Pp=A*P*A'+Q;
% 칼만 이득 계산
K=Pp*H'*inv(H*Pp*H'+R);
% 추정값 계산
x=xp+K*(z-H*xp);
% 오차 공분산 계산
P=Pp-K*H*Pp;

volt=x;