#include<stdio.h>
int calculaterepayment( float loan,float interestrate,int years,float installment,float extrapayment,int year){
 if(loan<=0|| years==0){
 	printf("loan fully repaid or no years remaining");
 	return 0;
 }	
 loan=loan*(1+interestrate);
 float totalpayment=installment+extrapayment;
 float payment;
 if(totalpayment<loan){
 	payment=totalpayment;
 }else{
 	payment=loan;
 }
 printf("Year %d: Remaining loan = %.2f\n", year, loan);
 return payment+calculaterepayment(loan,interestrate,years-1,installment,extrapayment,year+1);
}
int main(){
	float loan=1000;
	float installment=0.45;
	int years=3;
	float extrapayment=1200.3;
	float interestrate=234.6;
	float totalpaid=calculaterepayment(loan,interestrate,years,installment,extrapayment,1);
	printf("%.2f\n", totalpaid);
	
}
