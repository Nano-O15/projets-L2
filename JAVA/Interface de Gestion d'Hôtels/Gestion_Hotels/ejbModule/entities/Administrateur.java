package entities;

import java.io.Serializable;

import javax.persistence.*;


@Entity
@Table(name="Administrateur")
@Embeddable
public class Administrateur implements Serializable{
	@Id
    @GeneratedValue(strategy=GenerationType.AUTO)
    @Column(name="ID_administrateur") private long id_admin;
    @Column(name="nom") private String nom;
    @Column(name="prénom") private String prenom;
    
    @OneToOne
    @JoinColumn(name="ID_administrateur") private Administrateur hadmin;

	public Administrateur(String nom, String prenom) {
		super();
		this.nom = nom;
		this.prenom = prenom;
	}

	public Administrateur() {
		super();
	}

	public String getNom() {
		return nom;
	}

	public void setNom(String nom) {
		this.nom = nom;
	}

	public String getPrenom() {
		return prenom;
	}

	public void setPrenom(String prenom) {
		this.prenom = prenom;
	}

	public long getId_admin() {
		return id_admin;
	}
}
