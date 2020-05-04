function x = naiv_gauss1(A) 
n=length(A)-1;
for k=1:n-1
   for i=k+1:n
       xmult=A(i,k)/A(k,k);
       for j=k+1:n
           A(i,j)=A(i,j)-xmult*A(k,j);
       end
       A(i,n+1)=A(i,n+1)-xmult*A(k,n+1);
   end
end
x(n,1)=A(n,n+1)/A(n,n);
for i=n-1:-1:1
    sum=A(i,n+1);
    for j=i+1:n
       sum=sum-A(i,j)*x(j); 
    end
    x(i,1)=sum/A(i,i);
end
end