function x = Jordan_gauss(A)
n=length(A)-1;
for k=1:n
    A(k,:)=(1/A(k,k))*A(k,:);
    for i=k+1:n  %pivot기준 아래항 계수를 삭제
       xmult=A(i,k)/A(k,k);
       for j=k:n
           A(i,j)=A(i,j)-xmult*A(k,j);
       end
       A(i,n+1)=A(i,n+1)-xmult*A(k,n+1);
    end
    for i=k-1:-1:1 %pivot기준 윗항 계수를 삭제
       xmult=A(i,k)/A(k,k);
       for j=k:n
       A(i,j)=A(i,j)-xmult*A(k,j);
       end
    A(i,n+1)=A(i,n+1)-xmult*A(k,n+1);
    end
    disp(A)
end
for k=1:n
   x(k,1)=A(k,n+1); 
end