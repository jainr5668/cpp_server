import { Component, OnInit, Input, Output, EventEmitter } from '@angular/core';
import { Observable } from 'rxjs';
import { StringIds, StringIdsType } from 'src/stringIds';
import { TranslateService } from '@ngx-translate/core';
import { SignupModel } from './signup.model';
import { SignupRequestModel, SignupService } from '@services/auth/signup';
import { CardModel } from '@patterns/card';
import { ElementModel } from '@patterns/element';
import { ContentModel } from '@patterns/content';
import { FooterModel, FooterTypeEnum } from '@patterns/footer';

@Component({
  selector: 'feature-signup',
  templateUrl: './signup.component.html',
  styleUrls: ['./signup.component.css'],
})
export class SignupComponent implements OnInit {
  @Input() public homepage: SignupModel;

  @Output() clickListener = new EventEmitter();

  card: CardModel;
  signupModel: SignupRequestModel = new SignupRequestModel();

  constructor(
    private translate: TranslateService,
    private signupService: SignupService
  ) { }


  ngOnInit(): void {
    this.createSignupCard()
  }

  createSignupCard() {
    let elements = [];
    let element = new ElementModel();

    // Creating Card
    this.card = new CardModel();

    // First Name
    element.textField('username', StringIds.cFIRSTNAME, this.signupModel, "username");
    element.colspan = 1;
    elements.push(element);

    // Mobile 1
    element = new ElementModel();
    element.numberField('mobile1', StringIds.cMOBILE1, this.signupModel, "mobile1");
    element.colspan = 1;
    elements.push(element);

    // Password
    element = new ElementModel();
    element.passwordField('password', StringIds.cPASSWORD, this.signupModel, "password");
    element.colspan = 1;
    elements.push(element);

    // Creating Content
    let content = new ContentModel();
    content.setContentValues('signup-content', StringIds.cSIGNUP);
    content.cols = 2;
    content.elements = elements;
    this.card.contents.push(content);

    const footer = new FooterModel(
      FooterTypeEnum.APPLY_CANCEL,
      'signup-footer',
      null,
      (event) => {
        this.submit(event);
      }
    );
    this.card.footer = footer;
  }

  submit($event) {
    this.signupService.post(SignupRequestModel, this.signupModel).subscribe(
      {
        next: response => {
          this.ngOnInit();
        },
        error: error => {
          console.log(error);
          alert('Error: ' + <any>error);
        }
      });
  }

  public getLocalizedString$(stringId: StringIdsType): Observable<string> {
    return this.translate.stream(stringId);
  }
}
