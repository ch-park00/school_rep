%%
function vel=Getvel()

persistent Velp Posp

if isempty(Posp)
    Posp=0;
    Velp=80;
end

dt=0.1;
w=0+10*randn;
% 위치=이전 위치+속도*시간
Posp=Posp+Velp*dt;
% 노이즈 섞인 속도 측정값
Velp=80+w;
vel=Velp;
