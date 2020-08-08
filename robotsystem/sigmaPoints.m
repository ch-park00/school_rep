%%
function [Xi W]=sigmaPoints(xm,P,kappa)
n=numel(xm);
Xi=zeros(n,2*n+1);
W=zeros(n,1);

Xi(:,1)=xm;
W(1)=kappa/(n+kappa);
% cholesky 변환 수행해 ui열벡터 구하기
U=chol((n+kappa)*P);

% 1~n번째 원소
for k=1:n
    Xi(:,k+1)=xm+U(k,:)';
    W(k+1)=1/(2*(n+kappa));
end
% n+1~2n+1번 원소
for k=1:n
    Xi(:,n+k+1)=xm-U(k,:)';
    W(n+k+1)=1/(2*(n+kappa));
end
