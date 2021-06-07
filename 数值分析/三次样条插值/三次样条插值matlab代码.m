%首先导入节点xi,yi数据值,及f"（a），f"（b）。
X=input('请用户输入节点xi（i=0,1...n)所组成的矩阵:');
Y=input('请用户输入节点yi（i=0,1...n)所组成的矩阵:');
M0=input('请输入f"（a）的值：');
Mn=input('请输入f"（b）的值：');
%求hi并放入H中
n=length(X);
H=zeros(1,n);
for i=2:n
    H(i)=X(i)-X(i-1);
end
%把miu i放入miu中,把lanmuda i放入lanmuda中，把di 放入D中
miu=ones(1,n-1);lanmuda=ones(1,n-1);D=zeros(1,n-1);
for i=2:(n-1)
    miu(i)=H(i)/(H(i)+H(i+1));
    lanmuda(i)=1-miu(i);
    D(i)=6/(H(i)+H(i+1))*((Y(i+1)-Y(i))/H(i+1)-(Y(i)-Y(i-1))/H(i));
end
%求三弯矩方程（A*M=b）系数矩阵A和b,M
%求A；
A=zeros(n-2);
for i=1:(n-2)
    A(i,i)=2;
end
for i=1:(n-3)
    A(i,i+1)=lanmuda(i+1);
end
for i=2:(n-2)
    A(i,i-1)=miu(i+1);
end
%求b；
b=zeros(1,(n-2))';
b(1)=D(2)-miu(2)*M0;
for i=2:(n-3)
    b(i)=D(i+1);
end
b(n-2)=D(n-1)-lanmuda(n-1)*Mn;
M=[M0,(inv(A)*b)',Mn];
%S(x)形成的矩阵S
S=zeros(n-1,4);
for i=1:(n-1)
    syms x;
   p=((X(i+1)-x)^3)/(6*H(i+1))*M(i)+((x-X(i))^3)/(6*H(i+1))*M(i+1)...
       +(Y(i)-(H(i+1)^2)/6*M(i))*(X(i+1)-x)/H(i+1)+...
       (Y(i+1)-(H(i+1)^2)/6*M(i+1))*(x-X(i))/H(i+1);
   S(i,:)=coeffs(p,x);
end
%输出函数
for i=1:n-1
    fprintf('从x(%d)到x(%d):%f+(%f)*x+(%f)*x^2+(%f)*x^3\n',...
        i-1,i,S(i,1),S(i,2),S(i,3),S(i,4))
end


