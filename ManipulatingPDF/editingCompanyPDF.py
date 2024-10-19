import fitz

def fill_pdf_pymupdf(input_pdf_path, output_pdf_path, data_dict):
    doc = fitz.open(input_pdf_path)

    # Iterate through each page and fill the widgets (form fields)
    for page in doc:
        widgets = page.widgets()  # Get all form fields (widgets) on the page
        if widgets:
            for field in widgets:
                field_name = field.field_name
                if field_name in data_dict:
                    field.field_value = data_dict[field_name]
                    field.update()

    # Save the filled PDF
    doc.save(output_pdf_path, incremental=False, deflate=True)
    print(f"Filled PDF saved as '{output_pdf_path}'")

    # Flatten the PDF to remove interactive form elements
    doc = fitz.open(output_pdf_path)
    for page in doc:
        page.clean_contents()  # Remove any interactive form fields to make content static
    flattened_output_path = 'flattened_' + output_pdf_path
    doc.save(flattened_output_path, deflate=True)
    print(f"Flattened PDF saved as '{flattened_output_path}'")

# New Data to fill in (Portuguese content)
data = {
    'nome_estagiario': 'João da Silva',
    'nome_empresa': 'Empresa Exemplo S.A.',
    'nome_curso': 'Curso Técnico em Informática',
    'periodo': '2023-10',
    'nota_interesse': '9',
    'nota_iniciativa': '8',
    'nota_cooperacao': '10',
    'nota_assiduidade': '9',
    'nota_pontualidade': '8',
    'nota_disciplina': '9',
    'nota_sociabilidade': '10',
    'nota_adaptabilidade': '9',
    'nota_responsabilidade': '10',
    'nota_etica': '10',
    'nota_media': '9.2',
    'atividades': 'Desenvolvimento de sistemas, manutenção de software e suporte técnico.',
    'observacoes': 'João demonstrou excelente adaptação ao ambiente de trabalho e boa capacidade de aprendizado.'
}

# Usage
fill_pdf_pymupdf('avaliacaoempresaeditavel.pdf', 'filled_form.pdf', data)
