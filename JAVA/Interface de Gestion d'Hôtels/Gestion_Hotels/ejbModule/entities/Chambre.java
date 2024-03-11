package entities;

import java.io.Serializable;

import javax.persistence.*;

@Entity
@Table(name="Chambre")
@Embeddable
public class Chambre implements Serializable{
	@Id
    @GeneratedValue(strategy=GenerationType.AUTO)
    @Column(name="ID_chambre") private long id_chambre;
    @Column(name="num_etage") private long num_etage;
    @Column(name="num_chambre") private long num_chambre;
    @Column(name="nb_lits") private long nb_lits;
    @Column(name="num_cle") private long num_cle;
    
	@ManyToOne
	@JoinColumn(name="code_hotel") private Hotel hcham;

	public Chambre(long num_etage, long num_chambre, long nb_lits, long num_cle, Hotel hcham) {
		super();
		this.num_etage = num_etage;
		this.num_chambre = num_chambre;
		this.nb_lits = nb_lits;
		this.num_cle = num_cle;
		this.hcham = hcham;
	}

	public Chambre() {
		super();
	}

	public Chambre( int num_chambre, int nb_lits, int num_cle, int num_etage) {
		super();
		this.num_chambre = num_chambre;
		this.nb_lits = nb_lits;
		this.num_cle = num_cle;
		this.num_etage = num_etage;
	}

	public long getNum_etage() {
		return num_etage;
	}

	public void setNum_etage(long num_etage) {
		this.num_etage = num_etage;
	}

	public long getNum_chambre() {
		return num_chambre;
	}

	public void setNum_chambre(long num_chambre) {
		this.num_chambre = num_chambre;
	}

	public long getNb_lits() {
		return nb_lits;
	}

	public void setNb_lits(long nb_lits) {
		this.nb_lits = nb_lits;
	}

	public long getNum_cle() {
		return num_cle;
	}

	public void setNum_cle(long num_cle) {
		this.num_cle = num_cle;
	}

	public Hotel getHcham() {
		return hcham;
	}

	public void setHcham(Hotel hcham) {
		this.hcham = hcham;
	}

	public long getId_chambre() {
		return id_chambre;
	}
}
