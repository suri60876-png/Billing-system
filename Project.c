#include <stdio.h>
#include <string.h>
#define MAX_ITEMS 100
typedef struct 
{
	char name[50];
	float price;
} Device;
typedef struct 
{
	char name[50];
	int quantity;
	float price;
	float total;
} Purchase;
int main()
{
	FILE *fp,*bill;
	Device devices[MAX_ITEMS];
	Purchase purchases[MAX_ITEMS];
	int deviceCount = 0, purchaseCount = 0;
	float grandTotal = 0, discount = 0, finalAmount = 0, gst=0;
	fp = fopen("devices.txt", "r");
	if (fp == NULL) 
	{
		printf("Error: Could not open file 'devices.txt'\n");
		return 1;
	}
	while (fscanf(fp, "%s %f", devices[deviceCount].name, &devices[deviceCount].price) != EOF) 
	{
		deviceCount++;
	}
	fclose(fp);
	if (deviceCount == 0) 
	{
		printf("No devices found in the file.\n");
		return 0;
	}
	bill = fopen("shop_bill.txt", "w");
	if (bill == NULL) 
	{
		printf("Error: Could not create shop_bill.txt\n");
		return 1;
	}
	printf("Welcome to the Electric Shop\n");
	printf("\nAvailable Devices:\n");
	printf("-----------------------------------\n");
	for (int i = 0; i < deviceCount; i++) 
	{
		printf("%d. %s - ₹%.2f\n", i + 1, devices[i].name, devices[i].price);
	}
	printf("-----------------------------------\n");int n;
	printf("\nHow many different devices do you want to buy? ");
	scanf("%d", &n);
	for (int i = 0; i < n; i++) 
	{
		int choice, qty;
		printf("\nEnter device number: ");
		scanf("%d", &choice);
		if (choice < 1 || choice > deviceCount) 
		{
			printf("Invalid choice. Skipping...\n");
			continue;
		}
		printf("Enter quantity for %s: ", devices[choice - 1].name);
		scanf("%d", &qty);
		strcpy(purchases[purchaseCount].name, devices[choice - 1].name);
		purchases[purchaseCount].quantity = qty;
		purchases[purchaseCount].price = devices[choice - 1].price;
		purchases[purchaseCount].total = qty * devices[choice - 1].price;
		grandTotal += purchases[purchaseCount].total;
		purchaseCount++;
		printf("Added: %s x%d = ₹%.2f\n",
		devices[choice - 1].name, qty, qty * devices[choice - 1].price);
	}
	discount = grandTotal * 0.10;
	gst = (grandTotal - discount) * 0.18;
	finalAmount = grandTotal - discount + gst;
	fprintf(bill,"\n==========================================\n");
	fprintf(bill," ELECTRIC SHOP BILL\n");
	fprintf(bill,"==========================================\n");
	fprintf(bill,"%-20s %-10s %-10s %-10s\n", "Device", "Qty", "Price", "Total");
	fprintf(bill,"------------------------------------------\n");
	printf("\n==========================================\n");
	printf(" ELECTRIC SHOP BILL\n");
	printf("==========================================\n");
	printf("%-20s %-10s %-10s %-10s\n", "Device", "Qty", "Price", "Total");
	printf("------------------------------------------\n");
	for (int i = 0; i < purchaseCount; i++) \
	{
		printf("%-20s %-10d ₹%-9.2f ₹%-9.2f\n",
		purchases[i].name,
		purchases[i].quantity,
		purchases[i].price,
		purchases[i].total);
	}
	fprintf(bill,"------------------------------------------\n");
	fprintf(bill,"Subtotal: ₹%.2f\n", grandTotal);
	fprintf(bill,"Discount (10%%): -₹%.2f\n", discount);
	fprintf(bill,"GST (18%%) : +₹%.2f\n",gst);
	fprintf(bill,"Final Amount: ₹%.2f\n", finalAmount);
	fprintf(bill,"==========================================\n");
	printf("------------------------------------------\n");
	printf("Subtotal: ₹%.2f\n", grandTotal);
	printf("Discount (10%%): -₹%.2f\n", discount);
	printf("GST (18%%) : +₹%.2f\n",gst);
	printf("Final Amount: ₹%.2f\n", finalAmount);
	printf("==========================================\n");
	printf("Thank you for shopping with us!\n");
	fclose(bill);
	return 0;
}
