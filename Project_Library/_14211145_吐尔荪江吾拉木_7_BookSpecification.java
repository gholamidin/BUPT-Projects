package homework7;

public class _14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_BookSpecification {
	private String isbn;
	private String title;
	private double price;
	private int type;
	_14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_BookSpecification(){
		
	}
	_14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_BookSpecification(String isbn,String title,int type,double price){
		this.isbn=isbn;
		this.title=title;
		this.type=type;
		this.price=price;
	}
	public String getIsbn() {
		return isbn;
	}
	public String getTitle() {
		return title;
	}
	public double getPrice() {
		return price;
	}
	public int getType() {
		return type;
	}
	public void setIsbn(String isbn) {
		this.isbn = isbn;
	}
	public void setTitle(String title) {
		this.title = title;
	}
	public void setPrice(double price) {
		this.price = price;
	}
	public void setType(int type) {
		this.type = type;
	}


}
