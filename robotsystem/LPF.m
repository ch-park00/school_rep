function xlpf=LPF(x)

persistent prevX
persistent firstrun

if isempty(firstrun)
   prevX=x;
   
   firstrun=1;
end
% 알파값 변화에 대한 분석, 이동평균 필터에서는 딜레이 발생하는 것을 설명
alpha=0.9;
xlpf=alpha*prevX+(1-alpha)*x;

prevX=xlpf;