package entities;

import java.io.Serializable;

import javax.persistence.*;

@Entity
@Table(name="Client")
@Embeddable
public class Client implements Serializable{
	@Id
    @GeneratedValue(strategy=GenerationType.AUTO)
    @Column(name="ID_client") private long id_client;
    @Column(name="num_client") private long num_client;
    @Column(name="nom_client") private String nom_client;
    @Column(name="prenom_client") private String prenom_client;
    @Column(name="num__tel_client") private long num_tel_client;
    
	@ManyToOne
	@JoinColumn(name="code_hotel") private Hotel hclient;

	public Client(long num_client, String nom_client, String prenom_client, long num_tel_client,
			Hotel hclient) {
		super();
		this.num_client = num_client;
		this.nom_client = nom_client;
		this.prenom_client = prenom_client;
		this.num_tel_client = num_tel_client;
		this.hclient = hclient;
	}
	
	public Client() {
		super();
	}

	public Client(String nom_client, String prenom_client, long num_tel_client) {
		super();
		this.nom_client = nom_client;
		this.prenom_client = prenom_client;
		this.num_tel_client = num_tel_client;
	}

	public Long getNum_client() {
		return num_client;
	}

	public void setNum_client(Long num_client) {
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

	public long getNum_tel_client() {
		return num_tel_client;
	}

	public void setNum_tel_client(long num_tel_client) {
		this.num_tel_client = num_tel_client;
	}

	public Hotel getHclient() {
		return hclient;
	}

	public void setHclient(Hotel hclient) {
		this.hclient = hclient;
	}

	public long getId_client() {
		return id_client;
	}
}
