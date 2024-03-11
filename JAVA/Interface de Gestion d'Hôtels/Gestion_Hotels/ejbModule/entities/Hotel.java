package entities;

import java.io.Serializable;

import javax.persistence.*;

import java.util.*;

@Entity
@Table(name="Hotel")
public class Hotel implements Serializable{
	@Id
    @GeneratedValue(strategy=GenerationType.AUTO)
    @Column(name="code_hotel") private Long code_hotel;
    @Column(name="nom") private String nom;
    @Column(name="nb_etoiles") private int nb_etoiles;
    
    @OneToOne(mappedBy="hadmin")
    @Embedded Administrateur admin;
    
    @OneToOne(mappedBy="hadresse")
    @Embedded Adresse adresse;
    
	@OneToMany(mappedBy="hcham",cascade=CascadeType.PERSIST)
	private Collection<Chambre> listeChambre;
	
	@OneToOne()
	private Chambre cham;
	
	@OneToMany(mappedBy="hclient",cascade=CascadeType.PERSIST)
	private Collection<Client> listeClient;
	
	@OneToOne()
	private Client client;
	
	@OneToMany(mappedBy="hfac",cascade=CascadeType.PERSIST)
	private Collection<Facture> listeFacture;
	
	@OneToOne()
	private Facture fac;
	
	@OneToMany(mappedBy="hreservation",cascade=CascadeType.PERSIST)
	private Collection<Reservation> listeReservation;
	
	@OneToOne()
	private Reservation reservation;
    
	public Hotel(Long code_hotel, String nom, int nb_etoiles, Administrateur admin, Adresse adresse,
			Collection<Chambre> listeChambre, Chambre cham, Collection<Client> listeClient, Client client,
			Collection<Facture> listeFacture, Facture fac, Collection<Reservation> listeReservation,
			Reservation reservation) {
		super();
		this.code_hotel = code_hotel;
		this.nom = nom;
		this.nb_etoiles = nb_etoiles;
		this.admin = admin;
		this.adresse = adresse;
		this.listeChambre = listeChambre;
		this.cham = cham;
		this.listeClient = listeClient;
		this.client = client;
		this.listeFacture = listeFacture;
		this.fac = fac;
		this.listeReservation = listeReservation;
		this.reservation = reservation;
	}

	public Hotel() {
		super();
	}

	public Hotel(String nom, int nb_etoiles) {
		this.nom = nom;
		this.nb_etoiles = nb_etoiles;
	}

	public String getNom() {
		return nom;
	}

	public void setNom(String nom) {
		this.nom = nom;
	}

	public int getNb_etoiles() {
		return nb_etoiles;
	}

	public void setNb_etoiles(int nb_etoiles) {
		this.nb_etoiles = nb_etoiles;
	}

	public Administrateur getAdmin() {
		return admin;
	}

	public void setAdmin(Administrateur admin) {
		this.admin = admin;
	}

	public Adresse getAdresse() {
		return adresse;
	}

	public void setAdresse(Adresse adresse) {
		this.adresse = adresse;
	}

	public Long getCode_hotel() {
		return code_hotel;
	}
}
