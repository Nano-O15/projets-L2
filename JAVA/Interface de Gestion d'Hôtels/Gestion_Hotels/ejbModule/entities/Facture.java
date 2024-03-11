package entities;

import java.io.Serializable;

import java.sql.Date;

import javax.persistence.*;

@Entity
@Table(name="Facture")
@Embeddable
public class Facture implements Serializable{
	@Id
	@GeneratedValue(strategy=GenerationType.AUTO)
	@Column(name="ID_facture") private long id_facture;	
	@Column(name="num_facture") private long num_facture;
	@Column(name="num_client") private long num_client;
	@Column(name="nom_client") private String nom_client;
	@Column(name="prenom_client") private String prenom_client;
	@Column(name="date_facture") private Date date_facture;
	@Column(name="num_chambre") private long num_chambre;
	@Column(name="date_debut_r") private Date date_debut_r;
	@Column(name="date_fin_r") private Date date_fin_r;
	@Column(name="prix_r") private long prix_r;
	
	@ManyToOne
	@JoinColumn(name="code_hotel") private Hotel hfac;
	
	public Facture(long num_facture, long num_client, String nom_client, String prenom_client,
			Date date_facture, long num_chambre, Date date_debut_r, Date date_fin_r, long prix_r, Hotel hfac) {
		super();
		this.num_facture = num_facture;
		this.num_client = num_client;
		this.nom_client = nom_client;
		this.prenom_client = prenom_client;
		this.date_facture = date_facture;
		this.num_chambre = num_chambre;
		this.date_debut_r = date_debut_r;
		this.date_fin_r = date_fin_r;
		this.prix_r = prix_r;
		this.hfac = hfac;
	}

	public Facture() {
		super();
	}

	public long getNum_facture() {
		return num_facture;
	}

	public void setNum_facture(long num_facture) {
		this.num_facture = num_facture;
	}

	public long getNum_client() {
		return num_client;
	}

	public void setNum_client(long num_client) {
		this.num_client = num_client;
	}

	public String getNom_client() {
		return nom_client;
	}

	public void setNom_client(String nom_client) {
		this.nom_client = nom_client;
	}

	public String getPrenom_client() {
		return prenom_client;
	}

	public void setPrenom_client(String prenom_client) {
		this.prenom_client = prenom_client;
	}

	public Date getDate_facture() {
		return date_facture;
	}

	public void setDate_facture(Date date_facture) {
		this.date_facture = date_facture;
	}

	public long getNum_chambre() {
		return num_chambre;
	}

	public void setNum_chambre(long num_chambre) {
		this.num_chambre = num_chambre;
	}

	public Date getDate_debut_r() {
		return date_debut_r;
	}

	public void setDate_debut_r(Date date_debut_r) {
		this.date_debut_r = date_debut_r;
	}

	public Date getDate_fin_r() {
		return date_fin_r;
	}

	public void setDate_fin_r(Date date_fin_r) {
		this.date_fin_r = date_fin_r;
	}

	public long getPrix_r() {
		return prix_r;
	}

	public void setPrix_r(long prix_r) {
		this.prix_r = prix_r;
	}

	public Hotel getHfac() {
		return hfac;
	}

	public void setHfac(Hotel hfac) {
		this.hfac = hfac;
	}

	public long getId_facture() {
		return id_facture;
	}

}
