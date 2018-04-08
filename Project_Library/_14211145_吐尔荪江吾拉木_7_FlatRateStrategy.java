package homework7;

public class _14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_FlatRateStrategy implements _14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_IPricingstrategy {
	private double discountPerBook;
	public _14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_FlatRateStrategy(double discountPerBook){
		this.discountPerBook=discountPerBook;
	}
	public double getSubtotal(_14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_SaleLineitem temp) {
		// TODO Auto-generated method stub
		return temp.getProdSpec().getPrice()-discountPerBook;
	}
	public double getDiscountPerBook() {
		return discountPerBook;
	}
	public void setDiscountPerBook(double discountPerBook) {
		this.discountPerBook = discountPerBook;
	}
}
