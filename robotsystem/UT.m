%%
function [xm,xcov]=UT(Xi,W,noiseCov)

[n,kmax]=size(Xi);
% 평균 계산
xm=0;
for k=1:kmax
    xm=xm+W(k)*Xi(:,k);
end

xcov=zeros(n,n);
% 공분산 계산
for k=1:kmax
    xcov=xcov+W(k)*(Xi(:,k)-xm)*(Xi(:,k)-xm)';
end
xcov=xcov+noiseCov;