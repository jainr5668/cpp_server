export class SignupModel {
  username: string;
  mobile1: number;
  password: string;

  constructor(jsonData?: any) {
    if (typeof jsonData == 'object') {
      this.username = jsonData['username'];
      this.password = jsonData['password'];
      this.mobile1 = jsonData['mobile1'];
    } else {
      this.username = '';
      this.password = '';
      this.mobile1 = 0;
    }
  }
}

export class SignupRequestModel {
  
  username: string;
  mobile1: number;
  password: string;


  constructor(jsonData?: any) {
    if (typeof jsonData == 'object') {
      this.username = jsonData['username'];
      this.password = jsonData['password'];
      this.mobile1 = jsonData['mobile1'];
    } else {
      this.username = '';
      this.password = '';
      this.mobile1 = 0;
    }
  }
}
