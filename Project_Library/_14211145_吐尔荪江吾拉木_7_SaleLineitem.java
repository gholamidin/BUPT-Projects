package homework7;

public class _14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_SaleLineitem{
	private int copies;
	private _14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_IPricingstrategy strategy;
	private _14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_BookSpecification ProdSpec;
	public _14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_SaleLineitem(int copies,_14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_BookSpecification 
			ProdSpec,_14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_IPricingstrategy strategy){
		this.copies=copies;
		this.strategy=strategy;
		this.ProdSpec=ProdSpec;
	}
	public double getSubTotal(){
		return copies*strategy.getSubtotal(this);
	}
	public int getCopies() {
		return copies;
	}
	public void setCopies(int copies) {
		this.copies = copies;
	}
	public _14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_IPricingstrategy getStrategy() {
		return strategy;
	}
	public void setStrategy(_14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_IPricingstrategy strategy) {
		this.strategy = strategy;
	}
	public _14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_BookSpecification getProdSpec() {
		return ProdSpec;
	}
	public void setProdSpec(_14211145_ÍÂ¶ûİ¥½­ÎáÀ­Ä¾_7_BookSpecification prodSpec) {
		this.ProdSpec = prodSpec;
	}

}
