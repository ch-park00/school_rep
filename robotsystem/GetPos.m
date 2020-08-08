%%
function [z vel]=GetPos()

persistent Velp Posp

if isempty(Posp)
    Posp=0;
    Velp=80;
end

dt=0.1;
% 노이즈
w=0+10*randn;
v=0+10*randn;
% 위치=이전위치*속도*시간+노이즈
z=Posp+Velp*dt+v;
% 노이즈 없는 참값
Posp=z-v;
% 속도
Velp=80+w;
vel=Velp;

