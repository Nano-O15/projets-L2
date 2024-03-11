package entities;

import java.io.Serializable;

import java.sql.Date;

import javax.persistence.*;

@Entity
@Table(name="Reservation")
@Embeddable
public class Reservation implements Serializable{
	@Id
    @GeneratedValue(strategy=GenerationType.AUTO)
	@Column(name="ID_reservation") private long id_reservation;
	@Column(name="nom_client") private String nom_client;
	@Column(name="prenom_client") private String prenom_client;
	@Column(name="date_debut_r") private long date_debut_r;
	@Column(name="date_fin_r") private long date_fin_r;
	
	//Hotel
	@ManyToOne
	@JoinColumn(name="Code_hotel") private Hotel hreservation;

	public Reservation(String nom_client, String prenom_client, long date_debut_r, long date_fin_r,
			Hotel hreservation) {
		super();
		this.nom_client = nom_client;
		this.prenom_client = prenom_client;
		this.date_debut_r = date_debut_r;
		this.date_fin_r = date_fin_r;
		this.hreservation = hreservation;
	}

	public Reservation() {
		super();
	}

	public Reservation(String nom_client, String prenom_client, long date_debut_r, long date_fin_r) {
		this.nom_client = nom_client;
		this.prenom_client = prenom_client;
		this.date_debut_r = date_debut_r;
		this.date_fin_r = date_fin_r;
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

	public long getDate_debut_r() {
		return date_debut_r;
	}

	public void setDate_debut_r(long date_debut_r) {
		this.date_debut_r = date_debut_r;
	}

	public long getDate_fin_r() {
		return date_fin_r;
	}

	public void setDate_fin_r(long date_fin_r) {
		this.date_fin_r = date_fin_r;
	}

	public Hotel getHreservation() {
		return hreservation;
	}

	public void setHreservation(Hotel hreservation) {
		this.hreservation = hreservation;
	}

	public long getId_reservation() {
		return id_reservation;
	}
}
